#ifndef BACKGROUNDDATA_H
#define BACKGROUNDDATA_H

#include "datatypes.h"

#include <drposition.h>

class BackgroundData
{
public:
  BackgroundData();

  void setPosition(QString t_position, DRBackgroundPosition t_data);
  QString getBackgroundFilename(QString t_position);
  QString getForegroundFilename(QString t_position);

  virtual int getVerticalPosition(double t_height) = 0;

  void setSettings(DRBackgroundSettings t_settings);
  DRBackgroundSettings getSettings();

  void setModelList(QStringList l_Models);
  QStringList getModelList();

  virtual void execLoadBackground(QString t_backgroundName) = 0;

private:
  DRBackgroundSettings mSettings;
  QMap<QString, DRBackgroundPosition> mPositions = {};
  QStringList m_ModelList = {};

private:
  QMap<QString, DRPosition> m_LegacyPositionMap{
      {
          "wit",
          DRPosition("witnessempty", "stand"),
      },
      {
          "def",
          DRPosition("defenseempty", "defensedesk"),
      },
      {
          "pro",
          DRPosition("prosecutorempty", "prosecutiondesk"),
      },
      {
          "jud",
          DRPosition("judgestand", "judgedesk"),
      },
      {
          "hld",
          DRPosition("helperstand", "helperdesk"),
      },
      {
          "hlp",
          DRPosition("prohelperstand", "prohelperdesk"),
      },
  };
};

#endif // BACKGROUNDDATA_H
