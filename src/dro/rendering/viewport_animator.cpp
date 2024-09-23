#include "viewport_animator.h"
#include "datatypes.h"
#include <QDebug>
#include <aoapplication.h>
#include "file_functions.h"
#include "modules/json/json_reader.h"

ViewportAnimator::ViewportAnimator()
{
}

ViewportAnimator *ViewportAnimator::LoadAnimation(QString animation)
{
  QString animationPath = AOApplication::getInstance()->get_base_path() + "animations/" + "characters/" + animation + ".json";

  if(file_exists(animationPath))
  {
    ViewportAnimator *newAnim = new ViewportAnimator();

    JSONReader animationReader;
    animationReader.ReadFromFile(animationPath);

    bool      playOnce = animationReader.getBoolValue("loop");
    QString   soundFile = animationReader.getStringValue("sound");
    int       frameRate = animationReader.getIntValue("framerate");

    newAnim->SetPlayOnce(!playOnce);

    QJsonArray variableArray = animationReader.getArrayValue("variables");

    for(QJsonValueRef variableObject : variableArray)
    {
      animationReader.SetTargetObject(variableObject.toObject());


      QString paramName = animationReader.getStringValue("name");
      QString type = animationReader.getStringValue("type");

      if(type == "vec3")
      {
        Vec3Animator *vecAnimator = new Vec3Animator();
        if(variableObject.toObject().contains("position"))
        {
          vecAnimator->AddKeyframe(0, animationReader.getVector3DValue("position"));
        }

        QJsonArray frameValues = animationReader.getArrayValue("frames");

        for(QJsonValueRef frame : frameValues)
        {
          animationReader.SetTargetObject(frame.toObject());

          int     time    = animationReader.getIntValue("time");
          QString vartype = animationReader.getStringValue("var");

          if(vartype == "X")
          {
            vecAnimator->AddKeyframe(AnimVecX, time, animationReader.getDoubleValue("value"));
          }
          else if(vartype == "Y")
          {
            vecAnimator->AddKeyframe(AnimVecY, time, animationReader.getDoubleValue("value"));
          }
          else if(vartype == "Z")
          {
            vecAnimator->AddKeyframe(AnimVecZ, time, animationReader.getDoubleValue("value"));
          }
          else if(vartype == "XYZ")
          {
            vecAnimator->AddKeyframe(time, animationReader.getVector3DValue("value"));
          }
        }
        vecAnimator->Cache();
        newAnim->SetAnimator(paramName, vecAnimator);
      }
    }

    return newAnim;
  }
  return nullptr;
}

void ViewportAnimator::OnUpdate(int deltatime)
{
  if(m_CurrentTime > m_DurationTime)
  {
    if(m_PlayOnce) return;
     m_CurrentTime = 0;
  }
  m_CurrentTime += deltatime;
}

QVector3D ViewportAnimator::GetVec3(QString name)
{
  QVector3D m_AnimatorValue;
  if(m_Vec3Animators.contains(name))
  {
    m_AnimatorValue = m_Vec3Animators[name]->GetCachedValue(m_CurrentTime);
  }

  return m_RelativeVectors[name] + m_AnimatorValue;
}

void Vec3Animator::Cache()
{
  for(int i = 0; i < m_EndMS; i += m_FrameRate)
  {
    QVector3D m_CurrentValue = {GetValue(AnimVecX, i), GetValue(AnimVecY, i), GetValue(AnimVecZ, i)};
    qDebug() << m_CurrentValue;
    m_CachedValues[i] = m_CurrentValue;
  }
}

void Vec3Animator::AddKeyframe(VectorAnimatorTypes type, int ms, float value)
{
  switch(type)
  {
    case AnimVecX:
      m_KeyframesX[ms] = value;
      break;

    case AnimVecY:
      m_KeyframesY[ms] = value;
      break;

    case AnimVecZ:
      m_KeyframesZ[ms] = value;
      break;

    default:
      break;
  }

  if(m_EndMS < ms) { m_EndMS = ms; }
}

void Vec3Animator::AddKeyframe(int ms, QVector3D value)
{
  m_KeyframesX[ms] = value.x();
  m_KeyframesY[ms] = value.y();
  m_KeyframesZ[ms] = value.z();

  if(m_EndMS < ms) { m_EndMS = ms; }
}

QVector3D Vec3Animator::GetCachedValue(int ms)
{
  if (m_CachedValues.isEmpty()) return QVector3D();

  auto it = m_CachedValues.lowerBound(ms);

  if (it != m_CachedValues.begin() && (it == m_CachedValues.end() || it.key() > ms))
    --it;

  return it.value();
}

float Vec3Animator::GetValue(VectorAnimatorTypes type, int currentTime)
{

  float previousValue = 0,   nextValue = 0;
  int   previousTime  = 0,   nextTime  = 0;

  QMap<int, float>::iterator iteratorFramePrevious, iteratorFrameNext;
  QMap<int, float>* keyframeTarget = nullptr;


  if      (type == AnimVecX) keyframeTarget = &m_KeyframesX;
  else if (type == AnimVecY) keyframeTarget = &m_KeyframesY;
  else if (type == AnimVecZ) keyframeTarget = &m_KeyframesZ;

  if (!keyframeTarget || keyframeTarget->isEmpty()) return 0;


  iteratorFrameNext = keyframeTarget->lowerBound(currentTime);

  if (iteratorFrameNext == keyframeTarget->end())
  {
    iteratorFramePrevious = std::prev(keyframeTarget->end());
    nextTime = previousTime = iteratorFramePrevious.key();
    nextValue = previousValue = iteratorFramePrevious.value();
  }
  else
  {
    nextTime = iteratorFrameNext.key();
    nextValue = iteratorFrameNext.value();

    iteratorFramePrevious = (iteratorFrameNext == keyframeTarget->begin()) ? iteratorFrameNext : std::prev(iteratorFrameNext);

    previousTime = iteratorFramePrevious.key();
    previousValue = iteratorFramePrevious.value();
  }

  qDebug() << "Previous: " << previousTime << " - " << previousValue;
  qDebug() << "Next: " << nextTime << " - " << nextValue;

  if(currentTime == nextTime) return nextValue;
  if(previousTime > currentTime) return previousValue;
  if(previousTime == nextTime) return nextValue;

  qint64 durationLength = nextTime - previousTime;
  qint64 durationPassed = currentTime - previousTime;
  float durationPercantage = (float)durationPassed / (float)durationLength;

  float valueTraveled = nextValue - previousValue;

  if(durationPercantage <= 0.5)
  {
    if(m_Curve == CurveEase)
    {
      durationPercantage = 2 * durationPercantage * durationPercantage;
    }
    if(m_Curve == CurveBezier)
    {
      durationPercantage = durationPercantage * durationPercantage * (3.0f - 2.0f * durationPercantage);
    }
    if(m_Curve == CurveParametric)
    {
      durationPercantage = (durationPercantage * durationPercantage) / (2.0f * ((durationPercantage * durationPercantage) - durationPercantage) + 1.0f);
    }
  }
  else
  {
    if(m_Curve == CurveEase)
    {
      durationPercantage -= 0.5;
      durationPercantage = 2 * durationPercantage * (1 - durationPercantage) + 0.5;
    }
    if(m_Curve == CurveBezier)
    {
      durationPercantage = durationPercantage * durationPercantage * (3.0f - 2.0f * durationPercantage);
    }
    if(m_Curve == CurveParametric)
    {
      durationPercantage = (durationPercantage * durationPercantage) / (2.0f * ((durationPercantage * durationPercantage) - durationPercantage) + 1.0f);
    }
  }

  float distanceTraveled = valueTraveled * durationPercantage;

  return previousValue + distanceTraveled;
}

void ViewportAnimator::SetAnimator(QString name, Vec3Animator *animator)
{
  m_Vec3Animators[name] = animator;
  int AnimatorLength = animator->GetLength();
  if(m_DurationTime < AnimatorLength) m_DurationTime = AnimatorLength;
};
