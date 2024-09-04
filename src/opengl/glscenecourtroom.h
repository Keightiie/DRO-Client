#ifndef GLSCENECOURTROOM_H
#define GLSCENECOURTROOM_H

#include <Neo/scene/scene_data.h>
#include "glfogobject.h"

class GLSceneCourtroom : public SceneData
{
public:
  GLSceneCourtroom();
  void CreateFog();
  void InitShaders();
  void UpdateDimensions(int w, int h);
  void SetFog(GLFogObject *l_Fog);

public:
  void Render(QOpenGLShaderProgram *t_shaderProgram, TextureManager *t_textureManager);

private:
  GLFogObject *m_Fog = nullptr;
  QOpenGLShaderProgram m_FogShader;
  bool m_ShaderLoaded = false;
};

#endif // GLSCENECOURTROOM_H
