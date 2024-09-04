#include "glscenecourtroom.h"

GLSceneCourtroom::GLSceneCourtroom()
{
}

void GLSceneCourtroom::CreateFog()
{
  m_Fog = new GLFogObject();
}

void GLSceneCourtroom::InitShaders()
{
  if (!m_FogShader.addShaderFromSourceFile(QOpenGLShader::Vertex, "base/models/shaders/fogShaderV.glsl")) {
    qDebug() << "Vertex shader error:" << m_FogShader.log();
    return;
  }

  if (!m_FogShader.addShaderFromSourceFile(QOpenGLShader::Fragment, "base/models/shaders/fogShaderF.glsl")) {
    qDebug() << "Fragment shader error:" << m_FogShader.log();
    return;
  }

  if (!m_FogShader.link()) {
    qDebug() << "Shader link error:" << m_FogShader.log();
    return;
  }

  if (!m_FogShader.bind()) {
    qDebug() << "Shader bind error:" << m_FogShader.log();
    return;
  }

  m_ShaderLoaded = true;
}

void GLSceneCourtroom::UpdateDimensions(int w, int h)
{
  m_Fog->UpdateDimensions(w, h, QVector4D());
}

void GLSceneCourtroom::SetFog(GLFogObject *l_Fog)
{

  if(!m_ShaderLoaded) InitShaders();
  m_Fog = l_Fog;
}

void GLSceneCourtroom::Render(QOpenGLShaderProgram *t_shaderProgram, TextureManager *t_textureManager)
{
  t_shaderProgram->bind();
  QMatrix4x4 l_ViewMatrix = getCamera()->GetProjectionMatrix(true);

  t_shaderProgram->setUniformValue("mvp_matrix", l_ViewMatrix);

  QMatrix3x3 l_normalMatrix = getCamera()->GetProjectionMatrix(false).normalMatrix();
  t_shaderProgram->setUniformValue("normal_matrix", l_normalMatrix);
  t_shaderProgram->setUniformValue("texture", 0);

  t_shaderProgram->setUniformValue("view_position", QVector3D(0.0f, 0.0f, 5.0f));
  UpdateShader(t_shaderProgram);

  for(SceneObject *l_ScenObj : getGameObjects())
  {
    if(l_ScenObj == nullptr) return;
    l_ScenObj->DrawObject(t_shaderProgram, t_textureManager);
  }

  m_FogShader.bind();
  if(m_Fog != nullptr)
  {
    m_Fog->Draw(&m_FogShader, t_textureManager);
  }

}
