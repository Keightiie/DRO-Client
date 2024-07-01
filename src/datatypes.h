#ifndef DATATYPES_H
#define DATATYPES_H

#include "modules/globals/dro_math.h"
#include "qdebug.h"
#include "qvector2d.h"
#include <QDateTime>
#include <QMap>
#include <QVector>


enum class ChatTypes
{
  Talk,
  Shout,
  Think,
  CG,
  Narrator
};

class GameShoutData
{
public:
  GameShoutData(QString t_name)
  {
    mName = t_name;
  };

  QString mName = "";
  int mLegacyId = -1;
};

class GameEffectData
{
public:
  GameEffectData(QString t_name)
  {
    mName = t_name;
  };

  QString mName = "";
  bool mLoops = false;
  bool mIgnoresPair = false;
  int mLegacyId = -1;
};

class ReplayOperation
{
public:
  ReplayOperation(QString t_operation)
  {
    mOperation = t_operation;
  };
  QString mOperation = "";
  int mTimestamp = 0;
  QMap<QString, QString> mVariables = {};
};

class FreeblockData
{
public:
  FreeblockData(QString t_name)
  {
    mName = t_name;
  };
  QString mName = "";
  QString mImagePath = "";
  QMap<QString, QString> mVariables = {};
};

class SpeakerData
{
public:
  SpeakerData(QString t_chara, QString t_sprite)
  {
    mCharacter = t_chara;
    mEmote = t_sprite;
  };
  QString mCharacter = "";
  QString mEmote = "";
};

enum AnimTypes
{
  eAnimationShout,
  eAnimationGM,
  eAnimationEffects,
  eAnimationPlayer,
  eAnimationTheme
};

enum AnimationVariableTypes
{
  ePOS_X,
  ePOS_Y,
  eVarWidth,
  eVarHeight,
  eSCALE,
  eKEYFRAME,
  eALPHA,
  eFIXED_HEIGHT,
  eROTATION,
  eNONE
};

enum AnimCurveType
{
  LINEAR,
  EASE,
  BEZIER,
  PARAMETRIC,
  NONE
};


class DROAnimationKeyframe
{
public:
  DROAnimationKeyframe(qint64 time, AnimationVariableTypes type, float value, AnimCurveType fin, AnimCurveType fout)
  {
    Time = time;
    Type = type;
    Value = value;
    FadeIn = fin;
    FadeOut = fout;
  };
  qint64 Time;
  AnimationVariableTypes Type;
  float Value;
  AnimCurveType FadeIn = LINEAR;
  AnimCurveType FadeOut = LINEAR;
};

enum ThemeSceneType
{
  SceneTypeLobby,
  SceneTypeCourtroom,
  SceneTypeTestingLab,
  SceneTypeReplays,
  SceneTypeViewport
};

class EvidenceData
{
public:
  QString mName = "???";
  QString mDescription = "No Description Provided.";
  QString mImage = "";
};

class DRBackgroundSettings
{
public:
  bool isDynamic = false;
  double mScaleMinimum = 0.1;
  double mScaleMax = 0.9;
  double mPositionMinimum = 0;
  double mPositionMaximum = 1;
};

class DRBackgroundPosition
{
public:
  QString mBackground = "";
  QString mForeground = "";
};


class DREmote
{
public:
  QString character;
  QString key;
  QString comment;
  QString anim;
  QString dialog;
  int modifier = 0;
  int desk_modifier = -1;
  QString sound_file;
  int sound_delay = 0;
  QString video_file;
  QString outfitName = "";
  QString emoteName = "";
};

class DRAreaBackground
{
public:
  QString background;
  QMap<QString, QString> background_tod_map;
};

enum ClientId
{
  NoClientId = -1,
};

class DRChatRecord
{
public:
  DRChatRecord(QString p_name, QString p_message)
      : name(p_name)
      , message(p_message)
  {}

  QDateTime get_timestamp() const
  {
    return timestamp;
  }
  QString get_name() const
  {
    return name;
  }
  QString get_message() const
  {
    return message;
  }
  int get_client_id() const
  {
    return client_id;
  }
  bool is_self() const
  {
    return self;
  }
  bool is_system() const
  {
    return system;
  }
  bool is_music() const
  {
    return music;
  }

  // set
  void set_client_id(const int p_client_id)
  {
    client_id = p_client_id;
  }
  void set_self(const bool p_enabled)
  {
    self = p_enabled;
  }
  void set_system(bool p_enabled)
  {
    system = p_enabled;
  }
  void set_music(bool p_enabled)
  {
    music = p_enabled;
  }

private:
  QDateTime timestamp = QDateTime::currentDateTime();
  QString name;
  QString message;
  int client_id = NoClientId;
  bool self = false;
  bool system = false;
  bool music = false;
};

struct DRSfx
{
public:
  DRSfx() = default;
  DRSfx(QString p_name, QString p_file, bool p_is_found = false)
      : name(p_name.trimmed())
      , file(p_file.trimmed())
      , is_found(p_is_found)
  {}

  QString name;
  QString file;
  bool is_found;
};

class DRServerInfo
{
public:
  QString name;
  QString description;
  QString address;
  int port;

  QString to_info() const;
  QString to_address() const;

  bool operator==(const DRServerInfo &other) const;
  bool operator!=(const DRServerInfo &other) const;
};
using DRServerInfoList = QVector<DRServerInfo>;

class VersionNumber
{
public:
  int release = 0;
  int major = 0;
  int minor = 0;

  VersionNumber();
  VersionNumber(int release, int major, int minor);

  QString to_string() const;

  bool operator==(const VersionNumber &other) const;
  bool operator>(const VersionNumber &other) const;
  bool operator<(const VersionNumber &other) const;
};

enum class VersionStatus
{
  Ok,
  NotCompatible,
  ClientOutdated,
  ServerOutdated,
};

struct char_type
{
  QString name;
  bool taken = false;
};

struct pos_size_type
{
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

struct ThemeTabInfo
{
  QString m_Name = "chat";
  QString m_Group = "default";
  pos_size_type m_transform;
  QStringList m_WidgetContents = {};
};


struct dialogueHighlights
{
  QString chars = "";
  QString color = "#FFFFFF";
  bool keepCharacters = false;
};

struct widgetFontStruct
{
  QString font = "";
  int size = 20;
  bool bold = false;
  bool sharp = false;
  bool outline = false;
  QString color = "#FFFFFF";
  QString align = "left";
};

struct WidgetThemeData
{
  pos_size_type Transform;
  double Rotation = 0;
  widgetFontStruct *Font = nullptr;
  QVector2D Spacing = QVector2D(-1, -1);
};

enum SpriteCategory
{
  SpriteGUI,
  SpriteStage,
  SpriteCharacter,
  SpritePairCharacter,
  SpriteWeather,
  SpriteEffect,
  SpriteShout,
  SpriteSticker,
};

SpriteCategory string_to_sprite_category(QString p_category);
QString sprite_category_to_string(SpriteCategory p_category);
QStringList sprite_category_string_list();

enum ViewportSprite
{
  ViewportStageBack,
  ViewportStageFront,
  ViewportCharacterPre,
  ViewportCharacterIdle,
  ViewportCharacterTalk,
  ViewportPairCharacterIdle,
  ViewportWeather,
  ViewportEffect,
  ViewportShout,
};

SpriteCategory viewport_sprite_to_sprite_category(ViewportSprite p_type);

enum ChatCharaType : int32_t
{
  CharChara,
  CharNarrator,
  CharCG
};


enum MessagePacket : int32_t
{
  eMsClientToggles,
  eMsCharacterId,
  eMsCharacterFolder,
  eMsCharacterOutfit,
  eMsPreAnim,
  eMsCharacterEmote,
  eMsShowname,
  eMsTextContents,
  eMsSoundEffect,
  eMsSoundDelay,
  eMsTextColour,
  eMsShout,
  eMsEffects,
  eMsAnimation,
  eMsEvidenceName,
  eMsVideo,
  eMsClientId,
  eMsServerToggles,
  eMsAreaPosition,
  eMsOffsetX,
  eMsOffsetY,
  eMsPairCharaFolder,
  eMsPairCharaEmote,
  eMsPairOffsetX,
  eMsPairOffsetY
};

enum ChatMessage : int32_t
{
  CMDeskModifier = 0,
  CMPreAnim,
  CMChrName,
  CMEmote,
  CMMessage,
  CMPosition,
  CMSoundName,
  CMEmoteModifier,
  CMChrId,
  CMSoundDelay,
  CMShoutModifier,
  CMEvidenceId,
  CMFlipState,
  CMEffectState,
  CMTextColor,
  CMShowName,
  CMVideoName,
  CMHideCharacter,
  CMClientId,
  CMOffsetX,
  CMPairChrName,
  CMPairEmote,
  CMPairFlip,
  CMPairOffsetX,
  CMKeyframeAnim,
  CMCharType
};

enum EmoteMod
{
  IdleEmoteMod = 0,
  PreEmoteMod = 1,
  ZoomEmoteMod = 5,
  PreZoomEmoteMod = 6,
};


namespace DR
{
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
using SplitBehavior = QString::SplitBehavior;
#else
using SplitBehavior = Qt::SplitBehaviorFlags;
#endif
const SplitBehavior KeepEmptyParts = SplitBehavior::KeepEmptyParts;
const SplitBehavior SkipEmptyParts = SplitBehavior::SkipEmptyParts;

enum VAlign : int32_t
{
  Top,
  Middle,
  Bottom,
};

enum HAlign : int32_t
{
  Left,
  Center,
  Right,
};

enum Color : int32_t
{
  CDefault,
  CGreen,
  CRed,
  COrange,
  CBlue,
  CYellow,
  CPurple,
  CPink,
  CRainbow,

  // aliases
  CWhite = CDefault,
};

struct ColorInfo
{
public:
  ColorInfo() = default;
  ColorInfo(QString p_showname, QString p_code)
      : name(p_showname.toLower())
      , showname(p_showname)
      , code(p_code)
  {}

  QString name;
  QString showname;
  QString code;
};

QMap<Color, ColorInfo> get_default_color_map();
} // namespace DR

#endif // DATATYPES_H
