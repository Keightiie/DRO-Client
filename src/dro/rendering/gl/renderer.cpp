#include "renderer.h"
#include "buffers.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>


struct RendererStorage
{
  QOpenGLShaderProgram *m_UiShader;
  DROVertexBuffer *CubeQuad;
};

static RendererStorage* s_RendererData;

void Renderer::Init()
{

}
