#ifndef THEMEMODEREADER_H
#define THEMEMODEREADER_H

#include "json_reader.h"
#include "modules/json/theme_module_reader.h"

#include <aopixmap.h>
#include <datatypes.h>


class ThemeModeReader : public JSONReader
{
public:
  ThemeModeReader(QString filePath);
  ~ThemeModeReader();
  void LoadTimeMode();
  void LoadModules();

  QStringList GetDirectoryLoadOrder();

  void SetThemeJsonObject(QString category);

  void SetTimeOfDay(QString time);


  //IC Chatlog
  QColor getChatlogColour(QString t_type);
  bool getChatlogBool(QString t_type);
  bool getContainsChatlogColour(QString t_type);
  bool getContainsChatlogBool(QString t_type);


  //Data Retrieval
  QVector<ThemeTabInfo> getTabs();
  QVector<QStringList> getLayers();

  QHash<QString, dialogueHighlights>GetFontColorsHighlights();
  QMap<QString, DR::ColorInfo>GetFontColorsDefault();

  bool ContainsSoundName(QString setting);
  QString GetSoundName(QString setting);

  //Data Retrieval
  bool ContainsConfigToggle(QString setting);
  bool GetConfigToggle(QString setting);

  QVector2D getWidgetSpacing(QString widget_name);
  int getMusicScrollSpeed();
  int getTimerNumber();

  bool containsWidgetPosition(ThemeSceneType sceneType, QString name);

  pos_size_type getWidgetPosition(ThemeSceneType sceneType, QString name);

  bool containsWidgetFont(ThemeSceneType sceneType, QString widget_name);
  widgetFontStruct getWidgetFont(ThemeSceneType t_sceneType, QString t_name);

  pos_size_type getWidgetDimensions(QVector<ThemeScene *> t_readOrder, QString t_name);

  QVector<ThemeScene *> getSceneLoadOrder(ThemeSceneType t_type);
  QVector<ThemeModuleReader *>getModuleLoadOrder();

public:
  QHash<QString, AOPixmap> mThemeImages = {};

private:
  QString m_FilePath = "";
  int m_MusicDisplayScrollSpeed = -1;
  int m_TimerCount = -1;

  QMap<QString, DR::ColorInfo> m_CourtroomFontColorsDefault = {};
  QHash<QString, dialogueHighlights> m_CourtroomFontColorsHighlights = {};

  QString m_TimeOfDayCurrentName = "";
  ThemeModeReader* m_TimeOfDayCurrent = nullptr;
  QHash<QString, ThemeModeReader*> m_TimeOfDayReaders = {};

  QStringList m_ModuleNames = {};
  ThemeModuleReader* m_GamemodeModule = nullptr;
  QHash<QString, ThemeModuleReader*> m_TimeModules = {};
  QHash<QString, QHash<QString, ThemeModuleReader*>> m_ThemeModules = {};


};

#endif // THEMEMODEREADER_H
