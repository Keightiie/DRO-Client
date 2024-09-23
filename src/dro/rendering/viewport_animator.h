#ifndef VIEWPORT_ANIMATOR_H
#define VIEWPORT_ANIMATOR_H

#include <QMap>
#include <QString>
#include <QVector3D>


enum VectorAnimatorTypes
{
  AnimVecX   = 0,
  AnimVecY   = 1,
  AnimVecZ   = 2
};

enum AnimatorCurves
{
  CurveLinear,
  CurveEase,
  CurveBezier,
  CurveParametric,
  CurveNone
};

class KeyframeAnimator
{
public:
  virtual void Cache() = 0;
};

class Vec3Animator : public KeyframeAnimator
{
public:
  virtual void Cache() override;

  void AddKeyframe(VectorAnimatorTypes type, int ms, float value);
  void AddKeyframe(int ms, QVector3D value);
  QVector3D GetCachedValue(int ms);

  int GetLength() { return m_EndMS; }

private:
  float GetValue(VectorAnimatorTypes type, int frame);

private:
  //QMap<Time, QMap<Type, Value>>
  QMap<int, QVector3D> m_CachedValues = {};

  QMap<int, float> m_KeyframesX = {};
  QMap<int, float> m_KeyframesY = {};
  QMap<int, float> m_KeyframesZ = {};

  int m_FrameRate = 16;
  int m_EndMS = 0;

  AnimatorCurves m_Curve = CurveBezier;
};

class ViewportAnimator
{
public:
  ViewportAnimator();

  static ViewportAnimator *LoadAnimation(QString animation);

  void OnUpdate(int deltatime);
  void Restart() {m_CurrentTime = 0;};

  void SetPlayOnce(bool playOnce) {m_PlayOnce = playOnce;};

  void SetRelative(QString name, QVector3D vec){  m_RelativeVectors[name] = vec;  };
  void SetAnimator(QString name, Vec3Animator *animator);

  QVector3D GetVec3(QString name);
private:
  bool m_PlayOnce = true;
  int m_DurationTime = 0;
  int m_CurrentTime = 0;

  QMap<QString, QVector3D> m_RelativeVectors = {};
  QMap<QString, Vec3Animator*> m_Vec3Animators = {};
};

#endif // VIEWPORT_ANIMATOR_H
