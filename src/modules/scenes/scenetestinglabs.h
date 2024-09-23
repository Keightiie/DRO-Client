#ifndef SCENETESTINGLABS_H
#define SCENETESTINGLABS_H
#pragma once

#include <QObject>
#include <QWidget>
#include <qlineedit.h>
#include <aobutton.h>
#include <QTimer>
#include <dro/rendering/gl/buffers.h>
#include "dro/rendering/gl_viewport_widget.h"
#include "dro/rendering/rendering_layer.h"
#include "modules/widgets/keyframe_player.h"
#include "modules/scenes/viewport_scene.h"
#include "modules/theme/thememanager.h"
#include "modules/widgets/investigation_display.h"

class SceneTestingLabs : public QWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  explicit SceneTestingLabs(QWidget *parent = nullptr);
  void ConstructWidgets();

public slots:
  void ViewportLoaded();
  void ViewportUpdate();

private:
  QTimer *m_FrameTimer = new QTimer(this);
  NovelLayer *m_NovelLayer = nullptr;
  GLViewportWidget *m_Viewport = nullptr;
};

#endif // SCENETESTINGLABS_H
