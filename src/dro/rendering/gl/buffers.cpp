#include "buffers.h"
#include "QOpenGLWidget"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

DROVertexBuffer::DROVertexBuffer(QVector<DROVertexData> tVertex)
{
  initializeOpenGLFunctions();
  bufferArray.create();
  bufferIndex.create();

  bufferArray.bind();
  bufferArray.allocate(tVertex.constData(), tVertex.size() * sizeof(DROVertexData));
  indexLength = tVertex.count();
}

DROVertexBuffer::~DROVertexBuffer()
{

}

void DROVertexBuffer::Bind()
{
}

void DROVertexBuffer::Draw(QOpenGLShaderProgram *shader)
{
  shader->bind();

  bufferArray.bind();
  int vertexLocation = shader->attributeLocation("a_Position");
  int locationTexCoord = shader->attributeLocation("a_TexCoord");

  shader->enableAttributeArray(vertexLocation);
  shader->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(DROVertexData));

  shader->enableAttributeArray(locationTexCoord);
  shader->setAttributeBuffer(locationTexCoord, GL_FLOAT, sizeof(QVector3D), 2, sizeof(DROVertexData));


  glDrawArrays(GL_TRIANGLES, 0, indexLength);
}

void DROVertexBuffer::Unbind()
{

}

void DROVertexBuffer::SetLayout()
{

}
