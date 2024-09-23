#include "gl_viewport_widget.h"
#include "QDebug"
#include "gl/renderer2d.h"

void GLViewportWidget::TimerUpdate()
{
  emit FrameComplete();
  update();
}

void GLViewportWidget::paintGL()
{
}

void GLViewportWidget::initializeGL()
{
  initializeOpenGLFunctions();

  QSurfaceFormat l_SurfaceFormat;
  l_SurfaceFormat.setSwapInterval(1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_DEPTH_TEST);

  Renderer2D::Init();

  emit GLInitialize();
}

void GLViewportWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
  //QMatrix4x4 l_Camera;
  //l_Camera.ortho(-480.0f, 480.0f, -272.0f, 272.0f, -1.0f, 1.0f);

  //m_UiShader->setUniformValue("u_ViewProjection", l_Camera);
}


