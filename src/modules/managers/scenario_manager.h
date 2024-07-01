#ifndef SCENARIO_MANAGER_H
#define SCENARIO_MANAGER_H

#include <QString>
#include <datatypes.h>


class ICMessageData
{
public:
  ICMessageData(QStringList t_messageData, bool t_legacy);;
  QStringList LegacyPacketContents();
  QStringList PacketContents();

  bool m_DeskModifier = true;
  bool m_IsFlipped = false;
  bool m_HideCharacter = true;

  bool m_UsesPreAnimation = false;

  bool m_PairIsFlipped = false;
  bool m_PairIsHidden = false;

  QString m_PreAnimation = "";
  QString m_CharacterFolder = "";
  QString m_CharacterOutfit = "";
  QString m_CharacterEmotion = "";

  QString m_MessageContents = "";
  QString m_AreaPosition = "wit";
  QString m_SFXName = "";

  QString m_ShowName = "";
  QString m_VideoName = "";
  GameEffectData m_EffectData = GameEffectData("");

  QString m_PairCharacterFolder = "";
  QString m_PairCharacterEmotion = "";

  QString m_KeyframeAnimation = "";

  int m_EmoteModifier = 0; //CMEmoteModifier - Obsolete?
  int m_CharacterServerId = 0;
  int m_SFXDelay = 0;
  int m_ShoutModifier = 0;
  QString m_ShoutName = "";
  int m_EvidenceId = 0;


  int m_EffectState = 0;
  int m_TextColor = 0;
  int m_ClientId = 0;
  int m_OffsetX = 0;


  int m_PairOffsetX = 0;
  ChatTypes m_ChatType = ChatTypes::Talk;

};

class ScenarioManager
{
public:
  ScenarioManager();
};

#endif // SCENARIO_MANAGER_H
