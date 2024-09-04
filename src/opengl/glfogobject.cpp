#include "glfogobject.h"

GLFogObject::GLFogObject()
{
  initializeOpenGLFunctions();
  arrayBuf.create();
  indexBuf.create();
}

void GLFogObject::UpdateDimensions(int width, int height, QVector4D l_Color)
{
  QVector<FogShaderData> l_NewVerts;

  l_NewVerts.append({QVector3D(width / 2, -(height / 2), 0), l_Color, QVector2D(1.0f, 0.0f)}); // Red
  l_NewVerts.append({QVector3D(-(width / 2), height / 2, 0), l_Color, QVector2D(0.0f, 1.0f)}); // Green
  l_NewVerts.append({QVector3D(-(width / 2), -(height / 2), 0.0f), l_Color, QVector2D(0.0f, 0.0f)}); // Blue

  l_NewVerts.append({QVector3D(width / 2, -(height / 2), 0), l_Color, QVector2D(1.0f, 0.0f)}); // Red
  l_NewVerts.append({QVector3D(width / 2, height / 2, 0), l_Color, QVector2D(1.0f, 1.0f)}); // Green
  l_NewVerts.append({QVector3D(-(width / 2), height / 2, 0), l_Color, QVector2D(0.0f, 1.0f)}); // Blue

  m_GLVertices = l_NewVerts;
  Init();
}

void GLFogObject::Draw(QOpenGLShaderProgram *t_shaderProgram, TextureManager *t_textureManager)
{

  glEnable(GL_BLEND);
  glBlendFunc(GL_DST_COLOR, GL_ZERO);

  arrayBuf.bind();

  quintptr offset = 0;

  int l_ShadLocationPos = t_shaderProgram->attributeLocation("a_position");
  t_shaderProgram->enableAttributeArray(l_ShadLocationPos);
  t_shaderProgram->setAttributeBuffer(l_ShadLocationPos, GL_FLOAT, offset, 3, sizeof(FogShaderData));

  offset += sizeof(QVector3D);

  int l_ShadLocationColor = t_shaderProgram->attributeLocation("a_color");
  t_shaderProgram->enableAttributeArray(l_ShadLocationColor);
  t_shaderProgram->setAttributeBuffer(l_ShadLocationColor, GL_FLOAT, offset, 4, sizeof(FogShaderData));

  offset += sizeof(QVector4D);

  int l_ShadLocationUV = t_shaderProgram->attributeLocation("a_uv");
  t_shaderProgram->enableAttributeArray(l_ShadLocationUV);
  t_shaderProgram->setAttributeBuffer(l_ShadLocationUV, GL_FLOAT, offset, 2, sizeof(FogShaderData));

  glDrawArrays(GL_TRIANGLES, 0, m_GLVertices.count());


  glDisable(GL_BLEND);
}

void GLFogObject::Init()
{
  arrayBuf.bind();
  arrayBuf.allocate(m_GLVertices.constData(), m_GLVertices.size() * sizeof(FogShaderData));
}
