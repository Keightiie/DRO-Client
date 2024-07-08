#include "drmediatester.h"
#include "aoapplication.h"
#include "aoconfig.h"

#include <QUrl>

#include "debug_functions.h"

DRMediaTester::DRMediaTester(QObject *parent)
    : QObject(parent)
{
  AOApplication* ap_app = static_cast<AOApplication*>(parent);

  if (ap_app->ao_config->video_backend_vlc())
  {
    _vlcInstance = new VlcInstance(VlcCommon::args(), this);
    _vlcPlayer = new VlcMediaPlayer(_vlcInstance);

    connect(_vlcPlayer, SIGNAL(error()), this, SLOT(p_vlc_error()));
    _vlcMedia = new VlcMedia(QUrl("qrc:/data/sample.avi").toLocalFile(), true, _vlcInstance);
    _vlcPlayer->open(_vlcMedia);
  }
  else
  {
    m_player.setMuted(true);

    connect(&m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(p_check_status(QMediaPlayer::MediaStatus)));

    m_player.setMedia(QUrl("qrc:/data/sample.avi"));
  }
}

DRMediaTester::~DRMediaTester()
{}

void DRMediaTester::p_check_status(QMediaPlayer::MediaStatus p_status)
{
  switch (p_status)
  {
  case QMediaPlayer::InvalidMedia:
    call_warning("Your operating system appears to not currently support video playback. The video "
                 "playback will not work properly.<br /><br />In order for the feature to function properly, you "
                 "will need to install additional codecs or use libvlc in settings.<br /><br />"
                 "For more information visit "
                 "<a href=\"https://www.danganronpaonline.com\">https://www.danganronpaonline.com</a>");
    emit done();
    break;

  case QMediaPlayer::LoadedMedia:
    emit done();
    break;

  default:
    break;
  }
}

void DRMediaTester::p_vlc_error()
{
  call_warning("libVLC has failed to initialize");
  emit done();
}
