#ifndef VIEWPORT_ENTITY_H
#define VIEWPORT_ENTITY_H

#include <QVector>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include "dro/rendering/viewport_camera.h"
#include "dro/rendering/gl/buffers.h"
#include "dro_texture.h"
#include "dro/rendering/viewport_animator.h"

class ViewportEntity
{
public:
  ViewportEntity();

  void SetShader(QOpenGLShaderProgram * material);
  void SetCamera(ViewportCamera * camera);
  void LoadVerticies(QVector<DROVertexData> verticies);

  virtual void Draw();

  virtual void OnUpdate(float deltaTime) {};

public:
  void SetPosition(QVector3D position);
  void SetRotation(QVector3D rotation);
  void SetScale(QVector3D scale);

private:
  QVector3D m_PivotPoint = {960 / 2, 0, 0.0f};
  QVector3D m_Transform;
  QVector3D m_Rotation;
  QVector3D m_Scale = {1.0f, 1.0f, 1.0f};

  QOpenGLShaderProgram *m_Shader = nullptr;
  DROVertexBuffer *m_Buffer = nullptr;
  ViewportCamera *m_CameraTarget = nullptr;

};

class PlayerEntity : public ViewportEntity
{
public:
  PlayerEntity();
  virtual void Draw() override;
  virtual void OnUpdate(float deltaTime) override;

  void SetCharacter(QString character, QString emote);
  DROTexture *GetTexture() {return m_Texture;};

private:
  QRect m_TextureDimensions;
  DROTexture *m_Texture = nullptr;
  ViewportAnimator *m_Animator = nullptr;
  Vec3Animator *m_VecAnimator = nullptr;
  Vec3Animator *m_RotationAnimator = nullptr;

  ViewportCamera *m_PerspectiveAnimCam = nullptr;
};

#endif // VIEWPORT_ENTITY_H
