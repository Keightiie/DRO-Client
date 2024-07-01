#include "keyframe_player.h"
#include <QPaintEvent>
#include "aoapplication.h"
#include "modules/managers/scene_manager.h"
#include <modules/json/animation_reader.h>
#include "modules/managers/game_manager.h"
#include "modules/managers/animation_manager.h"

KeyframePlayer::KeyframePlayer(QWidget *parent) : DRGraphicsView(parent)
{
  setStyleSheet("background: transparent;");
  setBackgroundBrush(Qt::transparent);

  connect(&GameManager::get(), SIGNAL(ShoutComplete()), this, SLOT(animationComplete()));
  connect(&GameManager::get(), SIGNAL(JudgeComplete()), this, SLOT(animationComplete()));
}

bool KeyframePlayer::playAnimation(QString t_animation, AnimTypes t_type)
{
  mAnimType = t_type;
  if(!mObjectAnimations.isEmpty())
  {
    clearAniamtions();
  }
  bool animationExists = loadAnimation(t_animation);
  GameManager::get().SetAnimationGroup(mAnimType, mAnimatiorObjects);

  return animationExists;
}

bool KeyframePlayer::loadAnimation(QString t_animation)
{

  mAnimationObjects = {};
  mObjectAnimations = {};

  AnimationReader *l_reader = new AnimationReader(mAnimType, t_animation);
  mNames = l_reader->getObjectNames();

  QString l_animPath = l_reader->getAnimPath();
  int i = 0;
  for(QString r_name : mNames)
  {
    i++;

    DRSceneMovie * l_newObject = new DRSceneMovie(AOApplication::getInstance());
    scene()->addItem(l_newObject);
    l_newObject->setZValue(i);
    l_newObject->set_file_name(l_animPath + l_reader->getImageName(r_name));
    l_newObject->set_center_mode(false);
    l_newObject->set_scaling_mode(mk2::SpritePlayer::NoScaling);
    l_newObject->set_size(l_reader->getObjectSize(r_name));
    l_newObject->start();


    QString mMask = l_reader->getObjectMask(r_name);
    if(!mMask.isEmpty())
    {
      if(mAnimationObjects.contains(mMask))
      {
        //l_newObject->set_composition_mode(QPainter::CompositionMode_SourceAtop);
      }
    }


    GraphicObjectAnimator * l_newAnim = new GraphicObjectAnimator(l_newObject, 60);
    l_newAnim->setKeyframes(l_reader->getFrames(r_name));

    mAnimationObjects[r_name] = l_newObject;
    mObjectAnimations[r_name] = l_newAnim;
    mAnimatiorObjects.append(l_newAnim);
  }

  for(QString r_name : mNames)
  {
    mObjectAnimations[r_name]->startAnimation(false);
  }

  return l_reader->animationLoaded();
}

void KeyframePlayer::clearAniamtions()
{
  mNames.clear();
  for (auto it = mAnimationObjects.begin(); it != mAnimationObjects.end(); ++it) {
    delete it.value();
  }

  mAnimationObjects.clear();

  for (auto it = mObjectAnimations.begin(); it != mObjectAnimations.end(); ++it) {
    delete it.value();
  }
  mObjectAnimations.clear();

  mAnimatiorObjects.clear();
}

void KeyframePlayer::animationComplete()
{
  mFrameTimer.stop();
  clearAniamtions();
  if(mAnimType == eAnimationShout)
  {
    emit ShoutAnimationFinished();
  }
  if(mAnimType == eAnimationGM)
  {
    emit SplashAnimationFinished();
  }
  emit animationFinished();
}
