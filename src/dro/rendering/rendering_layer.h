#ifndef RENDERING_LAYER_H
#define RENDERING_LAYER_H
#include "dro_texture.h"
#include "gl/renderer2d.h"

#include <QString>

#include <modules/managers/scenario_manager.h>

#include <modules/background/background_data.h>
#include <QObject>
#include "dro/rendering/viewport_entity.h"

class RenderingLayer : public QObject
{
  Q_OBJECT
public:
  RenderingLayer();
  virtual void OnUpdate() = 0;
};

enum SpriteState
{
  ePre,
  eIdle
};

class NovelLayer : public RenderingLayer
{
  Q_OBJECT
public:
  NovelLayer();
  void OnUpdate() override;

  void UpdateBackground(QString background);
  void UpdateBgPosition(QString position);
  void UpdateNovel(ICMessageData message);

public slots:
  void PreAnimComplete();

private:
  DROTexture *m_BackgroundSprite = nullptr;


  SpriteState m_SpriteState = ePre;
  QString m_CharacterFolder = "";
  QString m_CharacterEmotion = "";


  QString m_BackgroundName = "";
  QString m_BackgroundPosition = "";

  BackgroundData *m_BackgroundData = nullptr;

  PlayerEntity *m_Player = nullptr;
};


#endif // RENDERING_LAYER_H
