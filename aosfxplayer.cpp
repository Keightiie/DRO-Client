#include "aosfxplayer.h"

#include <string.h>

#include <QDebug>

AOSfxPlayer::AOSfxPlayer(QWidget *parent, AOApplication *p_ao_app)
{
  m_parent = parent;
  ao_app = p_ao_app;


  BASS_Init(-1, 44100, BASS_DEVICE_LATENCY, 0, NULL);


}

void AOSfxPlayer::play(QString p_path)
{

  BASS_Stop();

  m_stream = BASS_StreamCreateFile(FALSE, p_path.toStdString().c_str(), 0, 0, BASS_STREAM_PRESCAN);

  /*
   if ((BASS_StreamPutFileData(
      m_stream,
      p_path.toStdString().c_str(),
      BASS_FILEDATA_END
  ) == -1))
   {
       qDebug() << "BASS_StreamPutFileData failllled!";
       qDebug() << "Error: " << QString::number(BASS_ErrorGetCode());
   }

  if (m_stream == 0)
  {
    qDebug() << "OHSHIT something broke. error code: " << QString::number(BASS_ErrorGetCode());
  }
  */

  //m_stream = BASS_StreamCreateFileUser(STREAMFILE_BUFFERPUSH, BASS_STREAM_AUTOFREE, nullptr, p_path.toStdString().c_str());

  if (BASS_ChannelPlay(m_stream, true))
    qDebug() <<"success.";
  else
    qDebug() <<"error";

  BASS_Start();

  qDebug() << QString::number(BASS_ErrorGetCode());
}