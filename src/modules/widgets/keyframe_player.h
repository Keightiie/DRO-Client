#ifndef KEYFRAMEPLAYER_H
#define KEYFRAMEPLAYER_H

#include <QObject>
#include <drgraphicscene.h>
#include <drscenemovie.h>

#include <modules/theme/droanimation.h>
#include <modules/theme/graphicobjectanimator.h>

class KeyframePlayer : public DRGraphicsView
{
  Q_OBJECT
public:
  KeyframePlayer(QWidget *parent = nullptr);
  bool playAnimation(QString t_animation, AnimTypes t_type);
  bool loadAnimation(QString t_animation);
  void updateView();

  void clearAniamtions();

public slots:
  void animationComplete();

signals:
  void SplashAnimationFinished();
  void ShoutAnimationFinished();
  void animationFinished();

private:
  QTimer mFrameTimer;
  DROAnimation *mAnimation = nullptr;
  QStringList mNames = {};
  QMap<QString, DRSceneMovie *> mAnimationObjects = {};
  QMap<QString, GraphicObjectAnimator *> mObjectAnimations = {};
  QVector<GraphicObjectAnimator *> mAnimatiorObjects = {};

  AnimTypes mAnimType = eAnimationTheme;



  bool flgUpdateRunning = false;
};

#endif // KEYFRAMEPLAYER_H
