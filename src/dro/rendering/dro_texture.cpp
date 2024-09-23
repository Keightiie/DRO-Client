#include "dro_texture.h"

#include <QImageReader>

DROTexture *DROTexture::Create(QString l_filePath)
{
  DROTexture *l_texture = new DROTexture(l_filePath);
  return l_texture;
}

DROTexture::DROTexture(QString l_filePath)
{
  QImageReader reader(l_filePath);
  QOpenGLTexture *m_Texture = nullptr;
  if (reader.supportsAnimation())
  {
    if(reader.format() == "webp")
    {
      while (reader.canRead())
      {
        QImage lFrame = reader.read();
        if (!lFrame.isNull())
        {
          m_Texture = new QOpenGLTexture(lFrame.mirrored());

          m_Texture->setMinificationFilter(QOpenGLTexture::Linear);
          m_Texture->setMagnificationFilter(QOpenGLTexture::Linear);
          m_Texture->setWrapMode(QOpenGLTexture::Repeat);

          m_Textures.push_back(m_Texture);
          m_FrameDelays.push_back(1000 / reader.nextImageDelay());
        }
        else
        {
          break;
        }
      }
    }
  }
  else
  {
    QImage lImage(l_filePath);

    m_Texture = new QOpenGLTexture(lImage.mirrored());

    m_Texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_Texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_Texture->setWrapMode(QOpenGLTexture::Repeat);

    m_Textures.push_back(m_Texture);
  }

  if(m_Textures.count() > 0)
  {
    m_Dimensions = {0, 0, m_Textures.at(0)->width(), m_Textures.at(0)->height()};

    float scaleFactor = static_cast<float>(544) / m_Textures.at(0)->height();

    int scaledWidth = static_cast<int>(m_Textures.at(0)->width() * scaleFactor);
    int scaledHeight = static_cast<int>(m_Textures.at(0)->height() * scaleFactor);

    m_ScaledDimensions = {480 - (scaledWidth / 2), 0, scaledWidth, scaledHeight};
  }

}

void DROTexture::UpdateDelay(int millisecond)
{
  if(m_Finished) return;
  m_LastDelayCount += millisecond;


  if(m_FrameDelays.count() > m_CurrentFrame)
  {
    if(m_LastDelayCount >= m_FrameDelays.at(m_CurrentFrame))
    {
      m_LastDelayCount = 0;
      m_CurrentFrame += 1;
    }
  }
  else
  {
    m_CurrentFrame = 0;
  }

  if(m_CurrentFrame > m_Textures.count() - 1)
  {
    m_CurrentFrame = 0;
    if(m_PlayOnce)
    {
      m_Finished = true;
      emit AnimationEnd();
    }
  }
}

void DROTexture::Bind()
{
  if(m_Textures.count() > 0)
  {
    m_Textures.at(m_CurrentFrame)->bind();
  }

}
