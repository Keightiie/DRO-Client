#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include "datatypes.h"

#include <modules/theme/graphicobjectanimator.h>
#include <modules/theme/thememanager.h>
#include "modules/widgets/typewritertextedit.h"
#include "qthread.h"
#include <drserversocket.h>
#include <modules/networking/dro_packet.h>
#include <modules/networking/network_handler.h>
#include <modules/networking/legacy_network_handler.h>
#include <modules/networking/neo_network_handler.h>
#include <neo/viewport/neo_renderer.h>

enum GameStates
{
  eStateDefault,
  eStateFreeCam
};

class GameManager : public QObject
{
  Q_OBJECT
public:
  GameManager(const GameManager&) = delete;

  static GameManager& get()
  {
    return s_Instance;
  }

  GameStates l_CurrentState = eStateDefault;

  void TogglePlayerInput(GameStates t_State, int l_key, bool t_toggle)
  {
    l_CurrentState = t_State;
    m_FreeCamInputs[l_key] = t_toggle;
  };

  void StartGameLoop();
  void StopGameLoop();
  void RestartGameLoop();

  void SetTrialCamera(int l_ID)
  {

    NeoRenderer *l_Renderer = ThemeManager::get().GetWidgetType<NeoRenderer>("opengl_display");
    if(l_Renderer == nullptr) return;

    m_CameraAnimation->AddKeyframe(m_GameUptime, eROTATION, l_Renderer->GetRotation().y(), EASE, EASE);
    m_CameraAnimation->AddKeyframe(m_GameUptime + 250, eROTATION, l_ID * 22.5, EASE, EASE);
    m_CameraAnimation->CacheAnimation();
    m_CameraAnimationStart = m_GameUptime;
  }

  NetworkHandler *GetNetworkHandlerCurrent()
  {
    return m_CurrentNetworkHandler;
  };

  bool IsGameLoopRunning()
  {
    return m_IsUpdateRunning;
  }

  void SetPlayerAnimation(GraphicObjectAnimator * t_animation);
  void SetTypeWriter(TypewriterTextEdit * t_writer);
  void SetAnimationGroup(AnimTypes t_type, QVector<GraphicObjectAnimator *> t_animations);

  void UpdateAnimationLoop(AnimTypes t_type);
  void RenderAnimationLoop(AnimTypes t_type);
  void UpdateCamera();

  //Data Gathering
  QString getShoutName(int t_id) { for(GameShoutData r_ShoutData : m_GameShouts) { if(t_id == r_ShoutData.mLegacyId) return r_ShoutData.mName; } return ""; }
  GameEffectData getEffect(QString t_name) { for(GameEffectData rEffectData : m_GameEffects) { if(t_name == rEffectData.mName) return rEffectData; } return GameEffectData("<NONE>"); }
  GameEffectData getEffect(int t_id) { for(GameEffectData rEffectData : m_GameEffects) { if(t_id == rEffectData.mLegacyId) return rEffectData; } return GameEffectData("<NONE>"); }

  //Setup
  void setupGame();


  //Server Stuff
  void SetupNetworkHandler();
  bool ProcessIncomingPacket(QString t_operation, QStringList t_parameters);
  void setServerFunctions(QStringList tFunctionList);
  bool usesServerFunction(QString tFunctionName);


  int getUptime();


public slots:
  void RunGameLoop();

signals:
  void FrameComplete();
  void JudgeComplete();
  void ShoutComplete();


private:

private:
  GameManager() {}
  static GameManager s_Instance;

  //Networking
  NetworkHandler *m_CurrentNetworkHandler = nullptr;

  //Game Loop Variables
  int m_FramesPerSecond = 60;
  bool m_IsUpdateRunning = false;

  //Game Timings
  QTimer m_FrameTimer;
  int m_GameUptime = 0;
  int m_CameraAnimationStart = 0;

  //Widgets
  TypewriterTextEdit *m_WidgetTypeWriter = nullptr;

  //Animations
  DROAnimation *m_CameraAnimation = nullptr;
  GraphicObjectAnimator *m_PlayerAnimation = nullptr;
  QMap<AnimTypes, QVector<GraphicObjectAnimator *>> m_GraphicObjectAnimations = {};

  //Data
  QVector<GameEffectData> m_GameEffects = {};
  QVector<GameShoutData> m_GameShouts = {};
  QStringList m_ServerFeatures = {};
  QMap<int, bool> m_FreeCamInputs = {};

  void setupGameEffects();
  void setupGameShouts();
};

#endif // GAMEMANAGER_H
