#ifndef VIEWPORT_SCENE_H
#define VIEWPORT_SCENE_H
#pragma once

#include <QObject>
#include <QWidget>
#include "modules/widgets/droviewportwidget.h"
#include <modules/widgets/keyframe_player.h>

class ViewportScene : public DROViewportWidget
{
  Q_OBJECT
public:
  ViewportScene(QWidget *parent = nullptr);

private:
};

#endif // VIEWPORT_SCENE_H
