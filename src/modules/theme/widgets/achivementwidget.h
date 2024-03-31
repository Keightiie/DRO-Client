#ifndef ACHIVEMENTWIDGET_H
#define ACHIVEMENTWIDGET_H

#include <QObject>
#include <QWidget>
#include <drstickerviewer.h>
#include <datatypes.h>
#include <drtextedit.h>
#include <aoimagedisplay.h>

class AchivementWidget : public QWidget
{
  Q_OBJECT
public:
  explicit AchivementWidget(QWidget *parent = nullptr);

  void SetAchivement(AF24Achivements t_achivement);
  void ThemeSetup();

public slots:
  void AchivementDone();

private:

  QTimer m_UpTimeTimer;

  DRStickerViewer *pBackgroundImage = nullptr;
  DRTextEdit *p_AchivementName = nullptr;
  AOImageDisplay *p_AchivementIcon = nullptr;

};

#endif // ACHIVEMENTWIDGET_H
