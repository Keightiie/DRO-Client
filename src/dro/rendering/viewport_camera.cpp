#include "viewport_camera.h"

ViewportCamera::ViewportCamera()
{
}

void ViewportCamera::SetPosition(QVector3D position)
{
  m_Position = position;
  UpdateMVP();
}

void ViewportCamera::SetRotation(QVector3D rotation)
{
  m_Rotation = rotation;
  UpdateMVP();
}

void ViewportCamera::SetProjection(float left, float right, float bottom, float top)
{
  m_ProjectionMatrix.ortho(left, right, bottom, top, -1.0f, 544.0f);
  UpdateMVP();
}

void ViewportCamera::SetProjection(float aspectRatio, float fov)
{
  m_ProjectionMatrix.perspective(fov, aspectRatio, 0.1f, 10000.0f);
  UpdateMVP();
}

void ViewportCamera::UpdateMVP()
{
  QMatrix4x4 l_Translation;
  l_Translation.translate(m_Position);

  QMatrix4x4 l_Rotation;
  l_Rotation.rotate(QQuaternion::fromEulerAngles(m_Rotation));

  m_ViewMatrix = l_Rotation * l_Translation;

  m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
