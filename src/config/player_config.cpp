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

int PlayerConfig::getInt(QString t_key, int t_default)
{
  if(m_ConfigValues.contains(t_key))
  {
    return m_ConfigValues[t_key];
  }
  else
  {
    m_ConfigValues[t_key] = t_default;
  }

  return t_default;
}

void PlayerConfig::setBool(QString t_key, bool t_value)
{
  m_ConfigToggles[t_key] = t_value;
}

void PlayerConfig::setInt(QString t_key, int t_value)
{
  m_ConfigValues[t_key] = t_value;
}

void PlayerConfig::saveConfig()
{

  QJsonObject l_FileObject;

  QJsonObject l_ConfigObject;

  for(QString l_stringKey : m_ConfigToggles.keys())
  {
    l_ConfigObject[l_stringKey] = m_ConfigToggles[l_stringKey];
  }

  for(QString l_stringKey : m_ConfigValues.keys())
  {
    l_ConfigObject[l_stringKey] = m_ConfigValues[l_stringKey];
  }

  for(QString l_stringKey : m_ConfigStrings.keys())
  {
    l_ConfigObject[l_stringKey] = m_ConfigStrings[l_stringKey];
  }

  l_FileObject["config"] = l_ConfigObject;


  QJsonDocument l_Document(l_FileObject);

  QFile l_File("base/configs/config.json");

  if (!l_File.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    qDebug() << "Failed to open file for writing.";
    return;
  }

  QTextStream l_TextStream(&l_File);
  l_TextStream.setCodec("UTF-8");
  l_TextStream << l_Document.toJson();

  l_File.close();
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
  QStringList l_IntValues = {"gl_fps", "gl_samples", "gl_swap"};
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

  for(QString r_intName : l_IntValues)
  {
    if(l_ConfigReader.isValueExists(r_intName))
    {
      m_ConfigValues[r_intName] = l_ConfigReader.getIntValue(r_intName);
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
