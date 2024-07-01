#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "src/aolabel.h"
#include "src/drgraphicscene.h"
#include "datatypes.h"
#include "game_manager.h"
#include <mk2/drplayer.h>
#include "modules/background/background_data.h"

#include <aoconfig.h>

#include "modules/scenes/scenetestinglabs.h"

class SceneManager
{
public:
  SceneManager(const SceneManager&) = delete;

  static SceneManager& get()
  {
    return s_Instance;
  }

  SceneTestingLabs *SceneConstructTestingLabs();


  ICMessageData *ProcessIncomingMessage(QStringList t_message);


  void execLoadPlayerBackground(QString t_backgroundName);
  DRBackgroundSettings getBackgroundSettings();
  int getBackgroundPosition();
  QString getBackgroundPath(QString t_position);
  QString getForegroundPath(QString t_position);


  AOLabel *CreateTransition(QWidget *parents, AOApplication* ao_app, DRGraphicsView *viewport);
  AOLabel *GetTransition();

  void RenderTransition();
  void AnimateTransition();
  void setFadeDuration(int duration);

  void clearPlayerDataList();

  QVector<DrPlayer> mPlayerDataList;

  AOConfig *pConfigAO = nullptr;

  //Current Scene
  void setCurrentSpeaker(QString t_chara, QString t_emote, int t_type);
  int getSpeakerType();
  SpeakerData getSpeakerCurrent();
  SpeakerData getSpeakerPrevious();
  QString getChatboxType();

public:
  ICMessageData *GetMessageData()
  {
    if(m_CurrentMessageData == nullptr)
    {
      m_CurrentMessageData = new ICMessageData({}, false);
    }
    return m_CurrentMessageData;
  }

  QString GetSpeakerAnimation()
  {
    return m_CurrentMessageData->m_KeyframeAnimation;
  }

private:
  SceneManager() {}
  static SceneManager s_Instance;


  //Widgets
  AOLabel *p_WidgetTransition = nullptr;
  DRGraphicsView *p_WidgetViewport = nullptr;

  int m_FadeDuration = 200;

  //Current Scene
  QString m_BackgroundName = "";
  BackgroundData *p_BackgroundCurrent = nullptr;
  SpeakerData   m_SpeakerCurrent = SpeakerData("", "");
  SpeakerData   m_SpeakerLast = SpeakerData("", "");
  int m_SpeakerType = 0;

  //Current Speaker
  ICMessageData *m_CurrentMessageData = nullptr;


  //Scenes
  SceneTestingLabs *m_SceneTestingLabs = nullptr;
};


#endif // SCENEMANAGER_H
