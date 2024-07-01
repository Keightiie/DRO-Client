#include "pair_manager.h"
#include "scene_manager.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "aoapplication.h"
#include "file_functions.h"
#include "datatypes.h"
#include "modules/background/background_reader.h"
#include "modules/background/legacy_background_reader.h"
#include "modules/managers/variable_manager.h"

SceneManager SceneManager::s_Instance;

SceneTestingLabs *SceneManager::SceneConstructTestingLabs()
{
  m_SceneTestingLabs = new SceneTestingLabs();
  m_SceneTestingLabs->show();
  return m_SceneTestingLabs;
}

ICMessageData *SceneManager::ProcessIncomingMessage(QStringList t_message)
{
  if(m_CurrentMessageData != nullptr) delete m_CurrentMessageData;
  m_CurrentMessageData = new ICMessageData(t_message, true);
  setCurrentSpeaker(m_CurrentMessageData->m_CharacterFolder, m_CurrentMessageData->m_CharacterEmotion, (int)m_CurrentMessageData->m_ChatType);
  return m_CurrentMessageData;
}

void SceneManager::execLoadPlayerBackground(QString t_backgroundName)
{
  m_BackgroundName = t_backgroundName;
  const QString l_backgroundJSONPath = AOApplication::getInstance()->find_asset_path(AOApplication::getInstance()->get_background_path(t_backgroundName) + "/" + "background.json");
  if(file_exists(l_backgroundJSONPath))
  {
    p_BackgroundCurrent = new BackgroundReader();
  }
  else
  {
    p_BackgroundCurrent = new LegacyBackgroundReader();
  }

  p_BackgroundCurrent->execLoadBackground(t_backgroundName);
}

int SceneManager::getBackgroundPosition()
{
  if(p_BackgroundCurrent == nullptr) return 0;
  return p_BackgroundCurrent->getVerticalPosition(0);
}

QString SceneManager::getBackgroundPath(QString t_position)
{
  if(p_BackgroundCurrent == nullptr) return "";
  QString l_filename = p_BackgroundCurrent->getBackgroundFilename(t_position);
  return AOApplication::getInstance()->get_background_sprite_path(m_BackgroundName, l_filename);
}

QString SceneManager::getForegroundPath(QString t_position)
{
  if(p_BackgroundCurrent == nullptr) return "";
  QString l_filename = p_BackgroundCurrent->getForegroundFilename(t_position);
  return AOApplication::getInstance()->get_background_sprite_path(m_BackgroundName, l_filename);
}

DRBackgroundSettings SceneManager::getBackgroundSettings()
{
  if(p_BackgroundCurrent == nullptr) return DRBackgroundSettings();
  return p_BackgroundCurrent->getSettings();
}

AOLabel *SceneManager::CreateTransition(QWidget *parents, AOApplication *ao_app, DRGraphicsView *viewport)
{
  p_WidgetTransition = new AOLabel(parents, ao_app);

  p_WidgetViewport = viewport;

  p_WidgetTransition->move(p_WidgetViewport->x(), p_WidgetViewport->y());
  p_WidgetTransition->resize(p_WidgetViewport->width(), p_WidgetViewport->height());

  return p_WidgetTransition;
}

AOLabel *SceneManager::GetTransition()
{
  return p_WidgetTransition;
}

void SceneManager::RenderTransition()
{
  QImage image(p_WidgetViewport->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::transparent);

  QPainter painter(&image);
  p_WidgetViewport->scene()->render(&painter);
  p_WidgetTransition->setPixmap(QPixmap::fromImage(image));
}

void SceneManager::AnimateTransition()
{
  QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
  p_WidgetTransition->setGraphicsEffect(eff);

  QPropertyAnimation *a = new QPropertyAnimation(eff, "opacity");
  a->setDuration(m_FadeDuration);
  a->setStartValue(1);
  a->setEndValue(0);
  a->setEasingCurve(QEasingCurve::OutBack);
  a->start(QPropertyAnimation::DeleteWhenStopped);
}

void SceneManager::setFadeDuration(int duration)
{
  m_FadeDuration = duration;
}

void SceneManager::clearPlayerDataList()
{
  mPlayerDataList.clear();
}

void SceneManager::setCurrentSpeaker(QString t_chara, QString t_emote, int t_type)
{
  m_SpeakerLast = SpeakerData(m_SpeakerCurrent.mCharacter, m_SpeakerCurrent.mEmote);
  m_SpeakerCurrent = SpeakerData(t_chara, t_emote);
  m_SpeakerType = t_type;
  VariableManager::get().setVariable("speaker_chara", m_SpeakerCurrent.mCharacter);
  VariableManager::get().setVariable("speaker_chara_last", m_SpeakerLast.mCharacter);
  VariableManager::get().setVariable("speaker_type", QString::number(t_type));
}

SpeakerData SceneManager::getSpeakerCurrent()
{
  return m_SpeakerCurrent;
}

SpeakerData SceneManager::getSpeakerPrevious()
{
  return m_SpeakerLast;
}

QString SceneManager::getChatboxType()
{

  if(m_SpeakerType == 1) return "shout";
  if(m_SpeakerType == 2) return "think";
  if(m_SpeakerType == 3) return "cg";

  if(!PairManager::get().GetUsePairData()) return "center";
  else
  {
    double l_offset_self = PairManager::get().GetOffsetSelf();
    double l_offset_pair = PairManager::get().GetOffsetOther();

    if(l_offset_self > l_offset_pair) return "right";
    else return "left";
  }
  return "center";
}

int SceneManager::getSpeakerType()
{
  return m_SpeakerType;
}


ICMessageData::ICMessageData(QStringList t_messageData, bool t_legacy)
{
  if(t_messageData.count() == 0) return;

  bool l_IsLatestServer = GameManager::get().usesServerFunction("v2");



  if(l_IsLatestServer)
  {
    QVector<bool> l_MessageStates = HexStringToBits(t_messageData[eMsClientToggles]);
    if(l_MessageStates.count() >= 4)
    {
      m_DeskModifier = l_MessageStates[0];
      m_UsesPreAnimation = l_MessageStates[1];
      m_IsFlipped = l_MessageStates[2];
      m_HideCharacter = l_MessageStates[3];
    }


    m_CharacterServerId = t_messageData[eMsCharacterId].toInt();

    m_CharacterFolder = t_messageData[eMsCharacterFolder];
    m_CharacterOutfit = t_messageData[eMsCharacterOutfit];
    m_PreAnimation = t_messageData[eMsPreAnim];
    m_CharacterEmotion = t_messageData[eMsCharacterEmote];
    m_ShowName = t_messageData[eMsShowname];
    m_MessageContents = t_messageData[eMsTextContents];
    m_SFXName = t_messageData[eMsSoundEffect];
    m_SFXDelay = t_messageData[eMsSoundDelay].toInt();
    m_TextColor = t_messageData[eMsTextColour].toInt();
    m_ShoutModifier = t_messageData[eMsShout].toInt();
    m_ShoutName = GameManager::get().getShoutName(m_ShoutModifier);
    m_EffectState = t_messageData[eMsEffects].toInt();
    m_EffectData = GameManager::get().getEffect(m_EffectState);
    m_KeyframeAnimation = t_messageData[eMsAnimation];
    //m_ShowName = t_messageData[eMsEvidenceName];
    m_VideoName = t_messageData[eMsVideo];
    m_ClientId = t_messageData[eMsClientId].toInt();
    //m_ShowName = t_messageData[eMsServerToggles];
    m_AreaPosition = t_messageData[eMsAreaPosition];
    m_OffsetX = t_messageData[eMsOffsetX].toInt();
    //m_ShowName = t_messageData[eMsOffsetY].toInt();
    m_PairCharacterFolder = t_messageData[eMsPairCharaFolder];
    m_PairCharacterEmotion = t_messageData[eMsPairCharaEmote];
    m_PairOffsetX = t_messageData[eMsPairOffsetX].toInt();
    //m_ShowName = t_messageData[eMsPairOffsetY];

    if(m_AreaPosition.trimmed().isEmpty()) m_AreaPosition = "wit";
  }
  else
  {
    m_DeskModifier = t_messageData[CMDeskModifier] == "1";
    m_PreAnimation = t_messageData[CMPreAnim];
    m_CharacterFolder = t_messageData[CMChrName];
    m_CharacterEmotion = t_messageData[CMEmote];

    m_MessageContents = t_messageData[CMMessage];
    m_AreaPosition = t_messageData[CMPosition];
    m_SFXName = t_messageData[CMSoundName];


    m_EmoteModifier = t_messageData[CMEmoteModifier].toInt();
    m_EffectData = GameManager::get().getEffect(m_EffectState);

    if(m_EmoteModifier == PreEmoteMod || m_EmoteModifier == PreZoomEmoteMod)
    {
      m_UsesPreAnimation = true;
    }
    else
    {
      m_UsesPreAnimation = false;
    }

    m_CharacterServerId = t_messageData[CMChrId].toInt();
    m_SFXDelay = t_messageData[CMSoundDelay].toInt();
    m_ShoutModifier = t_messageData[CMShoutModifier].toInt();
    m_ShoutName = GameManager::get().getShoutName(m_ShoutModifier);
    m_EvidenceId = t_messageData[CMEvidenceId].toInt();

    m_IsFlipped = t_messageData[CMFlipState] == "1";

    m_EffectState = t_messageData[CMEffectState].toInt();
    m_TextColor = t_messageData[CMTextColor].toInt();
    m_ShowName = t_messageData[CMShowName];
    m_VideoName = t_messageData[CMVideoName];
    m_HideCharacter = t_messageData[CMHideCharacter] == "1";
    m_ClientId = t_messageData[CMClientId].toInt();
    m_OffsetX = t_messageData[CMOffsetX].toInt();

    m_PairCharacterFolder = t_messageData[CMPairChrName];
    m_PairCharacterEmotion = t_messageData[CMPairEmote];
    m_PairIsFlipped = t_messageData[CMPairFlip] == "1";
    m_PairOffsetX = t_messageData[CMPairOffsetX].toInt();

    m_KeyframeAnimation = t_messageData[CMKeyframeAnim];
    m_ChatType = (ChatTypes)t_messageData[CMCharType].toInt();
  }


}

QStringList ICMessageData::LegacyPacketContents()
{
  QStringList l_returnData = {};

  bool l_non_legacy_server = GameManager::get().usesServerFunction("v2");

  l_returnData.append(QString::number(m_DeskModifier));
  l_returnData.append(m_PreAnimation);
  l_returnData.append(m_CharacterFolder);

  if (m_HideCharacter)
    l_returnData.append("../../misc/blank");
  else
    l_returnData.append(m_CharacterEmotion);

  l_returnData.append(m_MessageContents);

  l_returnData.append(m_AreaPosition);

  const QString l_sound_file = m_SFXName;
  l_returnData.append(l_sound_file.isEmpty() ? "0" : l_sound_file);

  l_returnData.append(QString::number(m_EmoteModifier));
  l_returnData.append(QString::number(m_CharacterServerId));

  l_returnData.append(QString::number(m_SFXDelay));

  l_returnData.append(QString::number(m_ShoutModifier));

  // Evidence
  l_returnData.append(QString::number(m_EvidenceId));

  l_returnData.append(QString::number(m_IsFlipped));

  l_returnData.append(QString::number(m_EffectState));

  l_returnData.append(QString::number(m_TextColor));

  l_returnData.append(m_ShowName);

  l_returnData.append(m_VideoName);

  l_returnData.append(QString::number(m_HideCharacter));

  if(l_non_legacy_server)
  {
    l_returnData.append(m_KeyframeAnimation);
    l_returnData.append(QString::number((int)m_ChatType));
  }

  return l_returnData;
}

QStringList ICMessageData::PacketContents()
{
  QStringList l_returnData = {};

  l_returnData.append(BitsToHexString({m_DeskModifier, m_UsesPreAnimation, m_IsFlipped, m_HideCharacter, m_ChatType == ChatTypes::CG}));
  l_returnData.append(QString::number(m_CharacterServerId));
  l_returnData.append(m_CharacterFolder);
  l_returnData.append(m_CharacterOutfit);
  l_returnData.append(m_PreAnimation);
  l_returnData.append(m_CharacterEmotion);
  l_returnData.append(m_ShowName);
  l_returnData.append(m_MessageContents);
  l_returnData.append(m_SFXName);
  l_returnData.append(QString::number(m_SFXDelay));
  l_returnData.append(QString::number(m_TextColor));
  l_returnData.append(QString::number(m_ShoutModifier));
  l_returnData.append(QString::number(m_EffectState));
  l_returnData.append(m_KeyframeAnimation);
  l_returnData.append(""); //Evidence
  l_returnData.append(m_VideoName);

  return l_returnData;
}
