#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <QMap>

class PlayerConfig
{
public:
  bool getBool(QString t_key, bool t_default = false);
  QString getString(QString t_key, QString t_default = "");
  int getInt(QString t_key, int t_default = 0);

  void setBool(QString t_key, bool t_value);
  void setInt(QString t_key, int t_value);

  void saveConfig();
  void loadConfig();

private:
  QMap<QString, QString> m_ConfigStrings = {};
  QMap<QString, bool> m_ConfigToggles = {};
  QMap<QString, int> m_ConfigValues = {};
};

extern PlayerConfig LOADED_CONFIG_DRO;

#endif // PLAYER_CONFIG_H
