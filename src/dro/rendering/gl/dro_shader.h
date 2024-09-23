#ifndef DRO_SHADER_H
#define DRO_SHADER_H

#include <QMap>
#include <QOpenGLShaderProgram>


class DROShader
{
public:
  static QOpenGLShaderProgram * GetShader(QString shaderName);

  static QMap<QString, QOpenGLShaderProgram *> SHADER_CACHE;
};

#endif // DRO_SHADER_H
