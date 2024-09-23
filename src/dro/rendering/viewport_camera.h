#ifndef VIEWPORT_CAMERA_H
#define VIEWPORT_CAMERA_H

#include <QMatrix4x4>


class ViewportCamera
{
public:
  ViewportCamera();

  void SetPosition(QVector3D position);
  void SetRotation(QVector3D rotation);
  void SetProjection(float left, float right, float bottom, float top);
  void SetProjection(float aspectRatio, float fov);

  QMatrix4x4 GetMatrix() { return m_ViewProjectionMatrix; };

private:
  void UpdateMVP();

private:
  bool m_IsOrtho = false;

  QVector3D m_Position;
  QVector3D m_Rotation;

  //Input
  QMatrix4x4 m_ProjectionMatrix;
  QMatrix4x4 m_ViewMatrix;

  //Calculated
  QMatrix4x4 m_ViewProjectionMatrix;
};

#endif // VIEWPORT_CAMERA_H
