#ifndef GL_VIEWPORT_WIDGET_H
#define GL_VIEWPORT_WIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <qopengltexture.h>
#include "dro_texture.h"
#include <QTimer>

#include "rendering_layer.h"

#include <dro/rendering/gl/buffers.h>

#include <modules/background/background_data.h>

class GLViewportWidget : public QGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GLViewportWidget(QWidget* l_parent) : QGLWidget(l_parent)
  {
    m_Timer = new QTimer();
    connect(m_Timer, &QTimer::timeout, this, &GLViewportWidget::TimerUpdate);
    m_Timer->start(16);
  };

public slots:
  void TimerUpdate();

signals:
  void FrameComplete();
  void GLInitialize();

protected:
  void paintGL() override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;

private:
  QTimer *m_Timer;
  RenderingLayer *m_Layer;

};

#endif // GL_VIEWPORT_WIDGET_H
