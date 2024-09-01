#include "player_config.h"

#include <modules/json/json_reader.h>

PlayerConfig LOADED_CONFIG_DRO;

bool PlayerConfig::getBool(QString t_variable, bool t_default)
{
  if(m_ConfigToggles.contains(t_variable))
  {
    return m_ConfigToggles[t_variable];
  }
  else
  {
    m_ConfigToggles[t_variable] = t_default;
  }
  return t_default;
}

QString PlayerConfig::getString(QString t_key, QString t_default)
{
  if(m_ConfigStrings.contains(t_key))
  {
    return m_ConfigStrings[t_key];
  }
  else
  {
    m_ConfigStrings[t_key] = t_default;
  }

  return t_default;
}

void PlayerConfig::saveConfig()
{

}

void PlayerConfig::loadConfig()
{
  //Clear the currently loaded config.
  m_ConfigStrings.clear();
  m_ConfigToggles.clear();

  //Load the config file
  JSONReader l_ConfigReader = JSONReader();

  //Setup the list of booleans and strings to check for.
  QStringList l_BoolValues = {"useOpenGL"};
  QStringList l_StringValues = {"msgBlipName"};

  l_ConfigReader.ReadFromFile("base/configs/config.json");
  l_ConfigReader.SetTargetObject("config");

  for(QString r_boolName : l_BoolValues)
  {
    if(l_ConfigReader.isValueExists(r_boolName))
    {
      m_ConfigToggles[r_boolName] = l_ConfigReader.getBoolValue(r_boolName);
    }
  }

  for(QString r_stringName : l_StringValues)
  {
    if(l_ConfigReader.isValueExists(r_stringName))
    {
      m_ConfigStrings[r_stringName] = l_ConfigReader.getStringValue(r_stringName);
    }
  }


}
