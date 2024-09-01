#include "background_reader.h"
#include "file_functions.h"

#include <aoapplication.h>

BackgroundReader::BackgroundReader()
{

}

void BackgroundReader::execLoadBackground(QString t_backgroundName)
{
  const QString l_backgroundJSONPath = AOApplication::getInstance()->find_asset_path(AOApplication::getInstance()->get_background_path(t_backgroundName) + "/" + "background.json");

  if(file_exists(l_backgroundJSONPath))
  {
    ReadFromFile(l_backgroundJSONPath);

    QStringList l_positions = {"wit", "def", "pro", "jud", "hld", "hlp"};
    for(QString l_pos : l_positions)
    {
      SetTargetObject("positions");
      
      if(isValueExists(l_pos))
      {
        SetTargetObject(l_pos);
        DRBackgroundPosition l_positionData;
        l_positionData.mBackground = getStringValue("background");
        l_positionData.mForeground = getStringValue("foreground");
        setPosition(l_pos, l_positionData);
      }

      ResetTargetObject();
    }

    setModelList(getStringArrayValue("models"));
    DRBackgroundSettings l_settings;
    SetTargetObject("scene");
    l_settings.m_ScenePosition = getVector3DValue("position");
    l_settings.m_SceneRotation = getVector3DValue("rotation");
    l_settings.m_LightPosition = getVector3DValue("light_position");
    l_settings.m_AmbientColor = getVector3DColorValue("ambient_color");
    l_settings.m_LightColor = getVector3DColorValue("light_color");
    ResetTargetObject();

    SetTargetObject("settings");
    l_settings.isDynamic = getBoolValue("dynamic");
    l_settings.mScaleMinimum = getDoubleValue("height_scale_minimum");
    l_settings.mScaleMax = getDoubleValue("height_scale_max");
    l_settings.mPositionMinimum = getDoubleValue("height_position_minimum");
    l_settings.mPositionMaximum = getDoubleValue("height_position_max");
    setSettings(l_settings);

  }
}

int BackgroundReader::getVerticalPosition(double t_height)
{
  return -230;
}
