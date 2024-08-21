#include "courtroom.h"

#include "draudioengine.h"

bool Courtroom::is_audio_suppressed() const
{
  return is_audio_muted;
}

void Courtroom::suppress_audio(bool p_enabled)
{
  is_audio_muted = p_enabled;

  // suppress audio
  for (auto &family : DRAudioEngine::get_family_list())
  {
    family->set_suppressed(is_audio_muted);
  }
}

void Courtroom::stop_all_audio()
{
  for (auto &family : DRAudioEngine::get_family_list())
    for (auto &stream : family->get_stream_list())
      stream->stop();
}

void Courtroom::keyPressEvent(QKeyEvent *event)
{
  if(m_RendererModeFree)
  {
    if(event->key() == Qt::Key_Escape)
    {
      m_RendererModeFree = false;
      p_WidgetOpenGL->setFocusPolicy(Qt::NoFocus);
      p_WidgetOpenGL->setCursor(Qt::BlankCursor);
      p_WidgetOpenGL->setMouseTracking(false);
      p_WidgetOpenGL->lower();
      ui_background->lower();
      GameManager::get().TogglePlayerInput(eStateDefault, event->key(), true);
    }
    else
    {
      GameManager::get().TogglePlayerInput(eStateFreeCam, event->key(), true);
    }
  }
}

void Courtroom::keyReleaseEvent(QKeyEvent *event)
{
  if(m_RendererModeFree)
  {
    GameManager::get().TogglePlayerInput(eStateFreeCam, event->key(), false);
  }
  else
  {
    GameManager::get().TogglePlayerInput(eStateDefault, event->key(), false);
  }
}

void Courtroom::mouseMoveEvent(QMouseEvent *event)
{
  if(m_RendererModeFree)
  {
    QPoint center = rect().center();
    QPoint delta = event->pos() - center;
    QVector3D l_CameraOffsets = QVector3D(delta.y(), delta.x(), 0)  * 0.15;

    p_WidgetOpenGL->TranslateRotation(l_CameraOffsets);

    QCursor::setPos(mapToGlobal(center));
  }
}
