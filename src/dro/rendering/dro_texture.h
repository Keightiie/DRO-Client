#ifndef DRO_TEXTURE_H
#define DRO_TEXTURE_H

#include <QOpenGLTexture>
#include <QObject>

class DROTexture : public QObject
{
  Q_OBJECT
public:
  static DROTexture* Create(QString l_filePath);
public:
  DROTexture(QString l_filePath);

  void UpdateDelay(int millisecond);;
  void Bind();

  int GetXValue() { return m_ScaledDimensions.x(); };
  int GetHeight() { return m_ScaledDimensions.height(); };
  int GetWidth() { return m_ScaledDimensions.width(); };

  void SetPlayOnce() {m_PlayOnce = true;};
  bool GetFinished() { return m_Finished; };

signals:
  void AnimationEnd();

private:
  QVector<QOpenGLTexture *> m_Textures = {};
  QVector<int> m_FrameDelays = {};

  QRect m_Dimensions = {};
  QRect m_ScaledDimensions = {};

  int m_LastDelayCount = 0;
  int m_CurrentFrame = 0;

  bool m_Finished = false;
  bool m_PlayOnce = false;
};

#endif // DRO_TEXTURE_H
