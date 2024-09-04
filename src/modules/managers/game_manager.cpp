#include "audio_manager.h"
#include "game_manager.h"
#include "pathing_manager.h"
#include "replay_manager.h"

#include <modules/json/json_reader.h>

#include <neo/viewport/neo_renderer.h>

GameManager GameManager::s_Instance;
GLSceneCourtroom NEO_SCENE_COURTROOM;
DRBackgroundSettings CURRENT_BACKGROUND;

void GameManager::StartGameLoop()
{
  m_CameraAnimation = new DROAnimation();
  m_CameraAnimation->SetAnimationLoops(false);

  ReplayManager::get().RecordingStart();
  connect(&m_FrameTimer, &QTimer::timeout, this, &GameManager::RunGameLoop);
  m_FrameTimer.setInterval(1000 / m_FramesPerSecond);
  m_FrameTimer.start();
}

void GameManager::StopGameLoop()
{
  m_WidgetTypeWriter = nullptr;
  m_PlayerAnimation = nullptr;
  m_GraphicObjectAnimations.clear();
  m_FrameTimer.stop();
}

void GameManager::RestartGameLoop()
{
  StopGameLoop();
  StartGameLoop();
}

void GameManager::SetPlayerAnimation(GraphicObjectAnimator *t_animation)
{
  m_PlayerAnimation = t_animation;
}

void GameManager::SetTypeWriter(TypewriterTextEdit *t_writer)
{
  m_WidgetTypeWriter = t_writer;
}

void GameManager::SetAnimationGroup(AnimTypes t_type, QVector<GraphicObjectAnimator *> t_animations)
{
  m_GraphicObjectAnimations[t_type] = t_animations;
}

void GameManager::UpdateAnimationLoop(AnimTypes t_type)
{
  if(m_GraphicObjectAnimations.contains(t_type))
  {
    bool l_AnimationQueueComplete = true;
    for(GraphicObjectAnimator * r_anim : m_GraphicObjectAnimations[t_type])
    {
      if(r_anim->getAnimation()->GetCurrentlyRunning())
      {
        l_AnimationQueueComplete = false;
        //r_anim->getAnimation()->RunAnimation();
      }
    }

    if(l_AnimationQueueComplete)
    {
      m_GraphicObjectAnimations[t_type] = {};
      if(t_type == eAnimationShout) emit ShoutComplete();
      if(t_type == eAnimationGM) emit JudgeComplete();
    }
  }
}

void GameManager::RenderAnimationLoop(AnimTypes t_type)
{
  if(m_WidgetTypeWriter != nullptr)
  {
    if(!m_WidgetTypeWriter->GetTypingComplete())
    {
      m_WidgetTypeWriter->UpdateDisplay();
    }
  }
  if(!m_GraphicObjectAnimations[t_type].empty())
  {
    bool lAllAnimationsDone = true;
    for(GraphicObjectAnimator * r_anim : m_GraphicObjectAnimations[t_type])
    {
      if(r_anim->getAnimation()->GetCurrentlyRunning())
      {
        lAllAnimationsDone = false;
        //r_anim->getAnimation()->RunAnimation();
        r_anim->updateAnimation();
      }
    }

    if(lAllAnimationsDone)
    {
      m_GraphicObjectAnimations[t_type] = {};
      if(t_type == eAnimationShout) emit ShoutComplete();
      if(t_type == eAnimationGM) emit JudgeComplete();
    }
  }
}


void GameManager::UpdateCamera()
{

  NeoRenderer *l_Renderer = ThemeManager::get().GetWidgetType<NeoRenderer>("opengl_display");
  if(l_Renderer == nullptr) return;
  if(!l_Renderer->IsRendering()) return;

  if(l_CurrentState == eStateFreeCam)
  {
    if(m_FreeCamInputs[Qt::Key::Key_W])
    {
      l_Renderer->TranslateTransform(QVector3D(0, 0, 0.1f));
    }
    if(m_FreeCamInputs[Qt::Key::Key_S])
    {
      l_Renderer->TranslateTransform(QVector3D(0, 0, -0.1f));
    }
    if(m_FreeCamInputs[Qt::Key::Key_A])
    {
      l_Renderer->TranslateTransform(QVector3D(0.1f, 0, 0));
    }
    if(m_FreeCamInputs[Qt::Key::Key_D])
    {
      l_Renderer->TranslateTransform(QVector3D(-0.1f, 0, 0));
    }
    //l_Renderer->update();
  }
  else
  {
    double l_Value = m_CameraAnimation->GetCachedValue(eROTATION, m_GameUptime);
    if(l_Value == -11037) return;
    l_Renderer->SetRotation(QVector3D(-5, l_Value, 0));
    //l_Renderer->update();
  }
  //l_Renderer->RendererUpdate();
  l_Renderer->update();
}


void GameManager::setupGame()
{
  PathingManager::get().CreateInitialFolders();
  setupGameEffects();
  setupGameShouts();
  StartGameLoop();
  AudioManager::get().InitializeAudio();
}


void GameManager::SetupNetworkHandler()
{
  if(usesServerFunction("IgnoreTSU"))
  {
    m_CurrentNetworkHandler = new NeoNetworkHandler();
  }
  else
  {
    m_CurrentNetworkHandler = new LegacyNetworkHandler();
  }
  m_CurrentNetworkHandler->GeneratePacketMap();
}

bool GameManager::ProcessIncomingPacket(QString t_operation, QStringList t_parameters)
{
  if(m_CurrentNetworkHandler == nullptr) return false;
  return m_CurrentNetworkHandler->ProcessPacket(t_operation, t_parameters);
}


void GameManager::setServerFunctions(QStringList tFunctionList)
{
  m_ServerFeatures.clear();
  m_ServerFeatures = tFunctionList;
  SetupNetworkHandler();
}

bool GameManager::usesServerFunction(QString tFunctionName)
{
  return m_ServerFeatures.contains(tFunctionName);
}

void GameManager::setupGameEffects()
{
  JSONReader lEffectsReader = JSONReader();
  lEffectsReader.ReadFromFile(PathingManager::get().getBasePath() +  "effects/default/effects.json");
  m_GameEffects = {};

  QJsonArray lEffectsArray = lEffectsReader.mDocument.array();
  for(QJsonValueRef rEffect : lEffectsArray)
  {
    lEffectsReader.SetTargetObject(rEffect.toObject());
    GameEffectData lEffectData = GameEffectData(lEffectsReader.getStringValue("effect_name"));
    lEffectData.mLoops = lEffectsReader.getBoolValue("loop");
    lEffectData.mIgnoresPair = lEffectsReader.getBoolValue("ignore_pair");
    lEffectData.mLegacyId = lEffectsReader.getIntValue("id");
    m_GameEffects.append(lEffectData);
  }
}

void GameManager::setupGameShouts()
{
  JSONReader l_ShoutsReader = JSONReader();
  l_ShoutsReader.ReadFromFile(PathingManager::get().getBasePath() +  "shouts/default/shouts.json");

  m_GameShouts = {};

  QJsonArray l_ShoutsArray = l_ShoutsReader.mDocument.array();
  for(QJsonValueRef r_shout : l_ShoutsArray)
  {
    l_ShoutsReader.SetTargetObject(r_shout.toObject());
    GameShoutData l_ShoutData = GameShoutData(l_ShoutsReader.getStringValue("shout_name"));
    l_ShoutData.mLegacyId = l_ShoutsReader.getIntValue("id");
    m_GameShouts.append(l_ShoutData);
  }
}

int GameManager::getUptime()
{
  return m_GameUptime;
}

void GameManager::RunGameLoop()
{
  if(!m_IsUpdateRunning)
  {
    m_GameUptime += 1000 / m_FramesPerSecond;
    m_IsUpdateRunning = true;

    if(m_PlayerAnimation != nullptr)
    {
      //m_PlayerAnimation->getAnimation()->RunAnimation();
      m_PlayerAnimation->updateAnimation();
    }

    RenderAnimationLoop(eAnimationShout);
    RenderAnimationLoop(eAnimationGM);
    UpdateCamera();

    m_IsUpdateRunning = false;
    emit FrameComplete();
  }
}
