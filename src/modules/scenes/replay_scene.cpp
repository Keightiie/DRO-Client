#include "replay_scene.h"
#include "commondefs.h"
#include "modules/theme/thememanager.h"
#include "modules/managers/scene_manager.h"
#include "qevent.h"
#include "modules/managers/game_manager.h"

#include <modules/managers/audio_manager.h>
#include <modules/managers/replay_manager.h>

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 13)
#else
#include <modules/networking/download_manager.h>
#include <modules/networking/network_downloader.h>
#endif

ReplayScene::ReplayScene(AOApplication *p_ao_app, QWidget *parent) : QWidget(parent)
{
  pAOApp = p_ao_app;
  constructWidgets();
  setWindowTitle("Replay");
  setFocusPolicy(Qt::StrongFocus);
  setAttribute(Qt::WA_DeleteOnClose, true );
}

ReplayScene::~ReplayScene()
{
  GameManager::get().SetTypeWriter(nullptr);
}

void ReplayScene::playSong(QString t_song)
{
  AudioManager::get().BGMPlay(t_song);
}

void ReplayScene::setText(QString t_dialogue)
{
  vpMessage->setTypewriterTarget(t_dialogue);
}

void ReplayScene::setMsgOperation(QMap<QString, QString> t_vars)
{
  mMsgVariables = t_vars;

  ICMessageData *m_MessageData = new ICMessageData({}, false);
  m_MessageData->m_ShowName = mMsgVariables["showname"];
  m_MessageData->m_CharacterFolder = mMsgVariables["char"];
  m_MessageData->m_SFXName = mMsgVariables["sound"];
  m_MessageData->m_CharacterEmotion = mMsgVariables["emote"];
  m_MessageData->m_PreAnimation = mMsgVariables["pre"];
  m_MessageData->m_VideoName = mMsgVariables["video"];
  m_MessageData->m_AreaPosition = mMsgVariables["pos"];
  m_MessageData->m_HideCharacter = mMsgVariables["hide"] == "1";
  m_MessageData->m_IsFlipped = mMsgVariables["flip"] == "1";
  m_MessageData->m_EffectData = GameManager::get().getEffect(mMsgVariables["effect"]);

  setText("");
  vpMessageShowname->setText(mMsgVariables["showname"]);

  ThemeManager::get().getWidget("chatbox")->setVisible(false);

  m_Viewport->ProcessIncomingMessage(m_MessageData);

  //mReplayScene->setText(mPlaybackReplay[mCurrentPlaybackIndex].mVariables["msg"]);
}

void ReplayScene::setBackground(QString t_name)
{
  SceneManager::get().execLoadPlayerBackground(t_name);
  m_Viewport->UpdateBackground("wit");
}

void ReplayScene::SetupReplayMetadata(int t_operationsCount)
{
  m_PlaybackScrubber->setMinimum(0);
  m_PlaybackScrubber->setMaximum(t_operationsCount - 1);
}


void ReplayScene::videoDone()
{

}

void ReplayScene::preanim_done()
{
  if(!mMsgVariables["msg"].trimmed().isEmpty()) ThemeManager::get().getWidget("chatbox")->setVisible(true);
  setText(mMsgVariables["msg"]);
}

void ReplayScene::OnScrubberSliderReleased()
{
  ReplayManager::get().PlaybackProgressSlider(m_PlaybackScrubber->value());
}

void ReplayScene::constructWidgets()
{
  ThemeManager::get().RegisterWidgetGenericBulk({});

  m_Viewport = new DROViewportWidget(this);
  ThemeManager::get().AutoAdjustWidgetDimensions(m_Viewport, "viewport", REPLAYS);
  ThemeManager::get().RegisterWidgetGeneric("viewport", m_Viewport);

  m_Viewport->ConstructViewport(REPLAYS);

  //UI Images
  ThemeManager::get().CreateWidgetImageDisplay("chatbox", "replay_chatmed.png", false, this);
  ThemeManager::get().CreateWidgetImageDisplay("vp_overlay", "replay_overlay.png", true, this);

  //Messagebox
  vpMessage = new TypewriterTextEdit(ThemeManager::get().getWidget("chatbox"));
  ThemeManager::get().AutoAdjustWidgetDimensions(vpMessage, "replay_message", REPLAYS);
  ThemeManager::get().RegisterWidgetGeneric("replay_message", vpMessage);
  vpMessage->setFrameStyle(QFrame::NoFrame);
  vpMessage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  vpMessage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  vpMessage->setReadOnly(true);
  GameManager::get().SetTypeWriter(vpMessage);
  set_drtextedit_font(vpMessage, "replay_message", REPLAYS_FONTS_INI, pAOApp);

  //Showname
  vpMessageShowname = new DRTextEdit(ThemeManager::get().getWidget("chatbox"));
  ThemeManager::get().AutoAdjustWidgetDimensions(vpMessageShowname, "replay_showname", REPLAYS);
  ThemeManager::get().RegisterWidgetGeneric("replay_showname", vpMessageShowname);
  vpMessageShowname->setFrameStyle(QFrame::NoFrame);
  vpMessageShowname->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  vpMessageShowname->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  vpMessageShowname->setReadOnly(true);
  set_drtextedit_font(vpMessageShowname, "replay_showname", REPLAYS_FONTS_INI, pAOApp);


  //Replay Controls
  m_PlaybackScrubber = new QSlider(Qt::Horizontal, this);
  ThemeManager::get().AutoAdjustWidgetDimensions(m_PlaybackScrubber, "scrubber", REPLAYS);
  ThemeManager::get().RegisterWidgetGeneric("scrubber", m_PlaybackScrubber);


  //Connections
  connect(m_Viewport, SIGNAL(VideoDone()), this, SLOT(videoDone()));
  connect(m_Viewport, SIGNAL(PreanimDone()), this, SLOT(preanim_done()));
  connect(m_PlaybackScrubber, SIGNAL(sliderReleased()), this, SLOT(OnScrubberSliderReleased()));

  //Extra Stuff
         //ThemeManager::get().createButtonWidget("return_to_lobby", this);

}


void ReplayScene::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Space)
  {
    ReplayManager::get().PlaybackProgressManual();
  }
  else
  {
    QWidget::keyPressEvent(event);
  }
}
