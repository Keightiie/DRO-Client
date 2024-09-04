#ifndef GLFOGOBJECT_H
#define GLFOGOBJECT_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <qopenglbuffer.h>
#include <Neo/Managers/texture_manager.h>


struct FogShaderData
{
  QVector3D m_Position;
  QVector4D m_Colors;
  QVector2D m_UVs;
};

class GLFogObject : protected QOpenGLFunctions
{
public:
  GLFogObject();
  void UpdateDimensions(int width, int height, QVector4D l_Color);
  void Draw(QOpenGLShaderProgram *t_shaderProgram, TextureManager *t_textureManager);
  void Init();

private:

  QString m_FogPath = "fog.png";
  QVector<FogShaderData> m_GLVertices;
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
};

#endif // GLFOGOBJECT_H
