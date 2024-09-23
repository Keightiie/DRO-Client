#include "dro_shader.h"

QMap<QString, QOpenGLShaderProgram *> DROShader::SHADER_CACHE = {};

QOpenGLShaderProgram * DROShader::GetShader(QString shaderName)
{
  QOpenGLShaderProgram * newShader = new QOpenGLShaderProgram();

  newShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "base/models/shaders/" + shaderName + ".v.glsl");
  newShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "base/models/shaders/" + shaderName + ".f.glsl");

  if (!newShader->link())
  {
    qDebug() << "Shader Program Link Error:" << newShader->log();
    return nullptr;
  }
  else
  {
    return newShader;
  }
}
