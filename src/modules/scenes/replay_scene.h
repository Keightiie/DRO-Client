#ifndef REPLAYSCENE_H
#define REPLAYSCENE_H

#include <QObject>
#include <QWidget>
#include <drcharactermovie.h>
#include "drgraphicscene.h"
#include "drscenemovie.h"
#include <aosfxplayer.h>
#include <aoapplication.h>
#include <aomusicplayer.h>
#include <dreffectmovie.h>
#include <drshoutmovie.h>
#include <drsplashmovie.h>
#include <drtextedit.h>
#include <qslider.h>
#include "modules/widgets/typewritertextedit.h"
#include <dro/rendering/gl_viewport_widget.h>
#include <mk2/graphicsvideoscreen.h>
#include <modules/widgets/droviewportwidget.h>
#include "modules/scenes/viewport_scene.h"
#include <modules/widgets/replay_hover_controller.h>
#include "dro/rendering/rendering_layer.h"

class ReplayScene : public QWidget
{
  Q_OBJECT
public:
  ReplayScene(AOApplication *p_ao_app, QWidget *parent = nullptr);
  ~ReplayScene();


  void playSong(QString t_song);
  void setMsgOperation(QMap<QString, QString> t_vars);
  void setBackground(QString t_name);
  void setWeather(QString t_weather);
  void playWTCE(QString t_name);

  void progressSlider(int t_progress);


  void SetupReplayMetadata(int t_operationsCount);

public slots:
  void videoDone();
  void preanim_done();
  void OnScrubberSliderReleased();
  void Frame();

private:
  AOApplication *pAOApp = nullptr;
  QMap<QString, QString> mMsgVariables = {};

  void constructWidgets();



protected:
  void keyPressEvent(QKeyEvent *event) override;

public slots:
  void ViewportLoaded();

private:
  //Viewport
  GLViewportWidget *m_GLViewport = nullptr;
  ViewportScene *m_Viewport = nullptr;

  DRTextEdit *vpShowname = nullptr;
  QSlider *m_PlaybackScrubber = nullptr;
  ReplayHoverController *m_ReplayHoverPanel = nullptr;
  NovelLayer *m_NovelLayer = nullptr;

  //To Be Moved

};

#endif // REPLAYSCENE_H
