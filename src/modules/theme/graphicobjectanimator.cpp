#include "graphicobjectanimator.h"
#include "qgraphicsscene.h"
#include "qtimer.h"

GraphicObjectAnimator::GraphicObjectAnimator(QGraphicsObject *t_widget, int t_framerate)
{
  mAnimationPlayer = new DROAnimation;
  mFrameRate = t_framerate;
  mTargetWidget = t_widget;
}

void GraphicObjectAnimator::startAnimation(bool t_loop)
{
  QRectF boundingRect = mTargetWidget->boundingRect();
  QPointF centerBottom(boundingRect.width() / 2.0, boundingRect.height());

  //mTargetWidget->setTransformOriginPoint(centerBottom);
  mAnimationPlayer->Start(t_loop);
  //updateAnimation();
}

void GraphicObjectAnimator::updateAnimation()
{
  if(!mAnimationPlayer->getIsPlaying()) return;

  float posX = mAnimationPlayer->getValue(ePOS_X);
  float posY = mAnimationPlayer->getValue(ePOS_Y);

  float lRotation = mAnimationPlayer->getValue(eROTATION);
  float lAlpha = mAnimationPlayer->getValue(eALPHA);

  float lScale = mAnimationPlayer->getValue(eSCALE);

  mTargetWidget->setX(posX);
  mTargetWidget->setY(posY);
  if(lScale != 9999999)
  {
    double l_scale = (lScale / 100);
    mTargetWidget->setScale(l_scale);
  }

  if(lRotation != 9999999)
  {
    mTargetWidget->setRotation(lRotation);
  }
  if(lAlpha != 9999999)
  {
    if (lAlpha != 0)
    {
      double opacity = (lAlpha / 255.0);
      mTargetWidget->setOpacity(opacity);
    }
    else
    {
      mTargetWidget->setOpacity(0);
    }
  }
}



void GraphicObjectAnimator::addKeyframe(qint64 time, AnimationVariableTypes type, float value, AnimCurveType fin, AnimCurveType fout)
{
  mAnimationPlayer->AddKeyframe(time, type, value, fin, fout);
}

void GraphicObjectAnimator::setKeyframes(QVector<DROAnimationKeyframe> t_frames)
{
  mAnimationPlayer->setKeyframes(t_frames);
}

DROAnimation *GraphicObjectAnimator::getAnimation()
{
  return mAnimationPlayer;
}