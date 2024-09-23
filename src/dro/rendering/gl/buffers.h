#ifndef BUFFERS_H
#define BUFFERS_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>

struct DROVertexData
{
  QVector3D m_Position;
  QVector2D m_TexCoord;
  //QVector3D m_Normals;
  //QVector3D m_JointIndices = QVector3D(0, -1, -1);
  //QVector3D m_JointWeights = QVector3D(1, 0, 0);
};

class DROVertexBuffer : protected QOpenGLFunctions
{
public:
  DROVertexBuffer(QVector<DROVertexData> tVertex);
  ~DROVertexBuffer();

  void Bind();
  void Draw(QOpenGLShaderProgram *shader);
  void Unbind();

  void SetLayout();

private:
  int indexLength;
  QOpenGLBuffer bufferArray;
  QOpenGLBuffer bufferIndex;
  int m_RendererID;
};

#endif // BUFFERS_H
