#include "background_data.h"

#include <aoapplication.h>

BackgroundData::BackgroundData()
{

}

void BackgroundData::setPosition(QString t_position, DRBackgroundPosition t_data)
{
  mPositions[t_position] = t_data;
}

QString BackgroundData::getBackgroundFilename(QString t_position)
{
  if(mPositions.contains(t_position))
  {
    if(!mPositions[t_position].mBackground.isEmpty())
    {
      return mPositions[t_position].mBackground;
    }
  }
  if(m_LegacyPositionMap.contains(t_position))
  {
    return m_LegacyPositionMap[t_position].get_back() + ".png";
  }

  return "";
}

QString BackgroundData::getForegroundFilename(QString t_position)
{
  if(mPositions.contains(t_position))
  {
    if(!mPositions[t_position].mForeground.isEmpty())
    {
      return mPositions[t_position].mForeground;
    }
  }

  return "";
}

void BackgroundData::setSettings(DRBackgroundSettings t_settings)
{
  mSettings = t_settings;
}

DRBackgroundSettings BackgroundData::getSettings()
{
  return mSettings;
}

void BackgroundData::setModelList(QStringList l_Models)
{
  m_ModelList = l_Models;
}

QStringList BackgroundData::getModelList()
{
  return m_ModelList;
}
