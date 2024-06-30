/**************************************************************************
**
** mk2
** Copyright (C) 2022 Tricky Leifa
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Affero General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Affero General Public License for more details.
**
** You should have received a copy of the GNU Affero General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/
#include "graphicsvideoscreen.h"
#include "courtroom.h"

#include <QAudioDeviceInfo>
#include <QAudioOutputSelectorControl>
#include <QMediaService>
#include <QStyleOptionGraphicsItem>
#include <QUrl>

#include <VLCQtCore/Audio.h>

DRVideoScreen::DRVideoScreen(AOApplication *ao_app, QGraphicsItem *parent)
    : QGraphicsVideoItem(parent)
    , ao_app(ao_app)
    , m_config(new AOConfig(this))
    , m_engine(new DRAudioEngine(this))
    , m_family(m_engine->get_family(DRAudio::Family::FVideo))
    , m_scanned(false)
    , m_video_available(false)
    , m_running(false)
    , m_player(new QMediaPlayer(this, QMediaPlayer::LowLatency))
{
  setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

  // Setup libvlc
  _vlcInstance = new VlcInstance(VlcCommon::args(), this);
  _vlcPlayer = new VlcMediaPlayer(_vlcInstance);

  _widget = ao_app->m_courtroom;
  _vlcWidget = new VlcWidgetVideo(_widget);
  _vlcWidget->setMediaPlayer(_vlcPlayer);
  _vlcPlayer->setVideoWidget(_vlcWidget);

  connect(_vlcPlayer, SIGNAL(stateChanged()), this, SLOT(vlc_stateChanged()));
  connect(_vlcPlayer, SIGNAL(mediaChanged()), this, SLOT(vlc_mediaChanged(libvlc_media_t*)));

  // Setup Qt Media Player
  m_player->setVideoOutput(this);

  connect(m_player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(update_video_availability(bool)));
  connect(m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(check_status(QMediaPlayer::MediaStatus)));
  connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(check_state(QMediaPlayer::State)));

  connect(m_engine, SIGNAL(current_device_changed(DRAudioDevice)), this, SLOT(update_audio_output()));
  connect(m_config, SIGNAL(video_volume_changed(int)), this, SLOT(update_volume()));
  connect(m_engine, SIGNAL(volume_changed(int32_t)), this, SLOT(update_volume()));
  connect(m_engine, SIGNAL(options_changed(DRAudio::Options)), this, SLOT(update_volume()));
  connect(m_family.get(), SIGNAL(volume_changed(int32_t)), this, SLOT(update_volume()));
  connect(m_family.get(), SIGNAL(options_changed(DRAudio::Options)), this, SLOT(update_volume()));

  update_audio_output();
}

DRVideoScreen::~DRVideoScreen()
{}

QString DRVideoScreen::get_file_name() const
{
  return m_file_name;
}

void DRVideoScreen::set_file_name(QString p_file_name)
{
  // if (m_file_name == p_file_name)
  // {
  //   return;
  // }
  stop();
  qInfo() << "loading media file" << p_file_name;
  m_scanned = false;
  m_video_available = false;
  m_file_name = p_file_name;
  if (m_file_name.isEmpty())
  {
    m_scanned = true;
  }
  if (ao_app->ao_config->video_backend_vlc())
  {
    _vlcMedia = new VlcMedia(m_file_name, true, _vlcInstance);
    _vlcPlayer->open(_vlcMedia);
  }
  else
  {
    m_player->setMedia(QUrl::fromLocalFile(m_file_name));
  }
}

void DRVideoScreen::play_character_video(QString p_character, QString p_video)
{
  QStringList l_filepath_list;
  const QString l_video_path = QString("videos/%1").arg(p_video);
  for (const QString &i_character_name : ao_app->get_char_include_tree(p_character))
  {
    l_filepath_list.append(ao_app->get_character_path(i_character_name, l_video_path));
  }

  const QString l_filepath = ao_app->find_asset_path(l_filepath_list);
  if (l_filepath.isEmpty())
  {
    qWarning() << "error: no character media file" << p_character << p_video;
    finish_playback();
    return;
  }
  set_file_name(l_filepath);
  play();
}

void DRVideoScreen::play()
{
  stop();
  m_running = true;
  if (!m_scanned)
  {
    return;
  }
  if (!m_video_available)
  {
    finish_playback();
    return;
  }
  start_playback();
}

void DRVideoScreen::stop()
{
  m_running = false;

  if ( _vlcPlayer->state() == Vlc::State::Playing)
  {
    _vlcPlayer->stop();
  }
  if (m_player->state() != QMediaPlayer::StoppedState)
  {
    m_player->stop();
  }
}

void DRVideoScreen::vlc_stateChanged()
{
  if (m_vlc_state == _vlcPlayer->state())
  {
    return;
  }
  // qDebug() << "//// STATE: " << _vlcPlayer->state() << " VLCMEDIA: " << _vlcMedia;
  m_vlc_state = _vlcPlayer->state();
  switch (m_vlc_state)
  {
  case Vlc::State::Error:
    m_scanned = true;
    qWarning() << "error: media file is invalid:" << m_file_name;
    finish_playback();
    break;

  case Vlc::State::Playing:
    emit started();
    start_playback();
    break;

  case Vlc::State::Ended:
    finish_playback();
    _vlcMedia->deleteLater();
    _vlcMedia = nullptr;
    _vlcWidget->hide();
    break;

  default:
    break;
  }
}

void DRVideoScreen::vlc_mediaChanged(libvlc_media_t* media)
{
  //qDebug() << "//// STATE: " << _vlcPlayer->state() << " MEDIA: " << media << " VLCMEDIA: " << _vlcMedia;
  // Currently this signal is not being called. Ignored for now.
}

void DRVideoScreen::update_video_availability(bool p_video_available)
{
  m_video_available = p_video_available;
}

void DRVideoScreen::check_status(QMediaPlayer::MediaStatus p_status)
{
  if (m_running)
  {
    switch (p_status)
    {
    case QMediaPlayer::InvalidMedia:
      m_scanned = true;
      qWarning() << "error: media file is invalid:" << m_file_name;
      finish_playback();
      break;

    case QMediaPlayer::NoMedia:
      m_scanned = true;
      finish_playback();

    case QMediaPlayer::LoadedMedia:
      m_scanned = true;
      if (m_video_available)
      {
        start_playback();
      }
      else
      {
        finish_playback();
      }
      break;

    default:
      break;
    }
  }
}

void DRVideoScreen::check_state(QMediaPlayer::State p_state)
{
  switch (p_state)
  {
  case QMediaPlayer::PlayingState:
    emit started();
    break;

  case QMediaPlayer::StoppedState:
    if (m_running)
    {
      finish_playback();
    }
    break;

  default:
    break;
  }
}

void DRVideoScreen::start_playback()
{
  if (ao_app->ao_config->video_backend_vlc())
  {
    _vlcPlayer->setPosition(0);
    update_volume();
    _vlcWidget->setGeometry(ao_app->m_courtroom->get_video_rect());
    _vlcWidget->show();
    _vlcWidget->activateWindow();
    _vlcWidget->raise();
  }
  else
  {
    if (m_player->state() == QMediaPlayer::StoppedState)
    {
      update_audio_output();

      m_player->play();
    }
  }
}

void DRVideoScreen::finish_playback()
{
  stop();
  emit finished();
}

void DRVideoScreen::update_audio_output()
{
  const auto l_target_device = m_engine->get_current_device();
  if (!l_target_device.has_value())
  {
    qWarning() << "error: no device to switch to";
    return;
  }

  QMediaService *l_service = m_player->service();
  if (!l_service)
  {
    qWarning() << "error: missing media service, device unchanged";
    return;
  }

  QAudioOutputSelectorControl *l_control = l_service->requestControl<QAudioOutputSelectorControl *>();
  if (!l_control)
  {
    qWarning() << "error: missing audio output control, device unchanged";
  }
  else
  {
    const QStringList l_device_name_list = l_control->availableOutputs();
    for (const QString &i_device_name : l_device_name_list)
    {
      const QString l_device_description = l_control->outputDescription(i_device_name);
      if (i_device_name == l_target_device->get_name() || i_device_name == l_target_device->get_driver() || l_device_description == l_target_device->get_name() || l_device_description == l_target_device->get_driver())
      {
        qDebug() << "Media player changed audio device to" << l_target_device->get_name();
        l_control->setActiveOutput(i_device_name);
        break;
      }
    }
    return;
  }
  l_service->releaseControl(l_control);

  update_volume();
}

void DRVideoScreen::update_volume()
{
  int l_volume = (m_family->get_volume() * m_engine->get_volume()) / 100;

  if (!m_family->is_ignore_suppression() && (m_family->is_suppressed() || m_engine->is_suppressed()))
  {
    l_volume = 0;
  }

  if (m_player->volume() != l_volume)
  {
    m_player->setVolume(l_volume);
  }

  // improve audio volume scaling for vlc since it's different from QMediaPlayer
  int transformed_volume = sqrt(sqrt(l_volume) * 10) * 10;
  if (_vlcPlayer->audio()->volume() != transformed_volume)
  {
    // qDebug() << "//// SET VOLUME " << l_volume << " LOG VOLUME " << transformed_volume;
    _vlcPlayer->audio()->setVolume(transformed_volume);
  }
}
