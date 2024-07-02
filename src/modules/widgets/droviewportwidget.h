#ifndef DROVIEWPORTWIDGET_H
#define DROVIEWPORTWIDGET_H

#include <DRCharacterMovie.h>
#include <DREffectMovie.h>
#include <DRSceneMovie.h>
#include <DRSplashMovie.h>
#include <QObject>
#include <QWidget>
#include <drgraphicscene.h>
#include <drshoutmovie.h>
#include "modules/managers/scenario_manager.h"
#include "keyframe_player.h"
#include "typewritertextedit.h"

#include <mk2/graphicsvideoscreen.h>

#include <aolabel.h>

class DROViewportWidget : public DRGraphicsView
{
  Q_OBJECT
public:
  explicit DROViewportWidget(QWidget *parent = nullptr);
  void ConstructViewport(ThemeSceneType t_scene);
  void ProcessIncomingMessage(ICMessageData *t_IncomingMessage);

  void TransitionRender();
  void TransitionAnimate();

  //
  void ConstructUserInterface();
  void ConstructText();
  void PlayShoutAnimation(QString t_name);
  void ToggleChatbox(bool t_state);

  //
  void PlaySplashAnimation(QString t_name);

  //Visual Updates
  void UpdateBackground(QString t_position = "wit");

  AOApplication *m_AOApp = nullptr;

signals:
  void VideoDone();
  void PreanimDone();
  void Resized();

public slots:
  void OnObjectionDone();
  void OnVideoDone();
  void OnPreanimDone();

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  DRGraphicsView *m_UserInterface = nullptr;
  KeyframePlayer *m_ShoutsPlayer = nullptr;

  //User Interface
  QMap<QString, DRSceneMovie*> m_UserInterfaceObjects = {};

  TypewriterTextEdit *m_TextMessage = nullptr;
  DRTextEdit *m_TextShowname = nullptr;


  //Data
  ICMessageData *m_IncomingMessage = nullptr;

  //Graphics Items
  DRSceneMovie *m_VpBackground = nullptr;
  DRCharacterMovie *m_VpPlayer = nullptr;

  //Animations
  DREffectMovie *m_VpEffect = nullptr;
  DRSplashMovie *m_VpWtce = nullptr;
  DRShoutMovie *m_VpShouts = nullptr;
  DRVideoScreen *m_VpVideo = nullptr;

  //Transition
  AOLabel *m_WidgetTransition = nullptr;
  int m_FadeDuration = 500;
};

#endif // DROVIEWPORTWIDGET_H
