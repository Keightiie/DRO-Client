#include "buffers.h"
#include "renderer2d.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "dro_shader.h"
#include <dro/rendering/gl/dro_shader.h>

struct Renderer2DStorage
{
  ViewportCamera *UserInterfaceCamera;
  ViewportEntity *InterfaceQuad;
};

static Renderer2DStorage* s_RendererData;

void Renderer2D::Init()
{
  s_RendererData = new Renderer2DStorage();

  s_RendererData->UserInterfaceCamera = new ViewportCamera();

  s_RendererData->UserInterfaceCamera->SetProjection(960.0f / 544.0f, 53.1f);
  s_RendererData->UserInterfaceCamera->SetPosition({-480.0f, -272.0f, -544.0f});

  //s_RendererData->UserInterfaceCamera->SetProjection(0.0f, 960.0f, 0.0f, 544.0f);
  //s_RendererData->UserInterfaceCamera->SetPosition({2.0f, 0.0f, 0});


  QVector<DROVertexData> l_verticies =
      {
          {{ 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
          {{ 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
          {{ 1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
          {{ 1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
          {{ 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
          {{ 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
      };

  s_RendererData->InterfaceQuad = new ViewportEntity();

  s_RendererData->InterfaceQuad->SetShader(DROShader::GetShader("UserInterface"));
  s_RendererData->InterfaceQuad->SetCamera(s_RendererData->UserInterfaceCamera);
  s_RendererData->InterfaceQuad->LoadVerticies(l_verticies);
}

void Renderer2D::ClearViewport()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer2D::DrawQuad(DROTexture *texture, QRect rect)
{
  texture->Bind();

  s_RendererData->InterfaceQuad->SetPosition({(float)rect.x(), (float)rect.y(), 0.0f});
  s_RendererData->InterfaceQuad->SetScale({(float)rect.width(), (float)rect.height(), 1.0f});
  s_RendererData->InterfaceQuad->Draw();
}

ViewportCamera *Renderer2D::GetInterfaceCamera()
{
  return s_RendererData->UserInterfaceCamera;
}
