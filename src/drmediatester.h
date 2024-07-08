#pragma once

#include <QMediaPlayer>
#include <QObject>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

class DRMediaTester : public QObject
{
  Q_OBJECT

public:
  DRMediaTester(QObject *parent = nullptr);
  ~DRMediaTester();

signals:
  void done();

private:
  QMediaPlayer m_player;
  VlcInstance *_vlcInstance;
  VlcMedia *_vlcMedia;
  VlcMediaPlayer *_vlcPlayer;


private slots:
  void p_check_status(QMediaPlayer::MediaStatus p_status);
  void p_vlc_error();
};
