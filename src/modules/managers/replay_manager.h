#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include <QElapsedTimer>
#include <QTimer>
#include <datatypes.h>
#include "scene_manager.h"

#include <modules/scenes/replay_scene.h>

class ReplayManager
{
public:
  ReplayManager(const ReplayManager&) = delete;

  static ReplayManager& get()
  {
    return s_Instance;
  }

  //Replay Recording Functions
  void RecordingStart();
  void RecordChangeMusic(QString t_music);
  void RecordChangeBackground(QString t_bgn);
  void RecordMessageIC(ICMessageData *m_Message);
  void RecordMessageOOC(QString t_name, QString t_message);
  void RecordPlaySplash(QString t_splash);
  void RecordChangeWeather(QString t_weather);
  void RecordChangeGamemode(QString t_gamemode);
  void RecordChangeHour(QString t_hour);
  void RecordChangeTOD(QString t_tod);
  void RecordingSave();


  //Playback Functions
  void PlaybackLoadFile(QString t_name, ReplayScene *p_scene);
  void PlaybackProgressManual();
  void PlaybackProgressSlider(int t_index);


  //Playback Metadata Functions
  QStringList getReplayList(QString t_package, QString t_category);
  QString getReplayPath(QString t_package, QString t_category, QString t_name);
  QString getReplayImagePath(QString t_package, QString t_category, QString t_name);

  //Package Functions
  QStringList getPackageNames();
  QVector<QString> getPackageCategoryList(QString t_package);

  void ResetPackagesCache();
  void CachePackageReplays(QString t_package, QVector<QString> t_tags);


private:
  ReplayManager() {}
  static ReplayManager s_Instance;

  ReplayScene *p_SceneReplay = nullptr;

  //Packages
  QVector<QString> m_PackagesContaining = {};
  QHash<QString, QVector<QString>> m_PackageCategories = {};

  //Recording
  QElapsedTimer m_TimerRecorder;
  QString m_FilePathOutput = "replays/replay.json";
  QVector<ReplayOperation> m_ReplayOperationsRecorded = {};

  //Playback
  int m_PlaybackPositionIndex = 0;
  QVector<ReplayOperation> m_ReplayOperationsPlayback = {};


};

#endif // REPLAYMANAGER_H
