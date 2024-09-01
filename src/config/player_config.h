#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <QMap>

class PlayerConfig
{
public:
  bool getBool(QString t_key, bool t_default = false);
  QString getString(QString t_key, QString t_default = "");

  void saveConfig();
  void loadConfig();

private:
  QMap<QString, QString> m_ConfigStrings = {};
  QMap<QString, bool> m_ConfigToggles = {};
};

extern PlayerConfig LOADED_CONFIG_DRO;

#endif // PLAYER_CONFIG_H
