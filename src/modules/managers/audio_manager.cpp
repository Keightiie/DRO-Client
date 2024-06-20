#include "audio_manager.h"
#include "aoapplication.h"
#include <QRegularExpression>
#include <aomusicplayer.h>
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 13)
#else
#include <modules/networking/download_manager.h>
#endif

AudioManager AudioManager::s_Instance;

void AudioManager::InitializeAudio()
{
  m_PlayerMusic = new AOMusicPlayer(AOApplication::getInstance());
  m_PlayerSFX = new AOSfxPlayer(AOApplication::getInstance());
}

void AudioManager::BGMPlay(QString t_track)
{
  QRegularExpression urlRegex("(http|https|ftp)://[^\\s/$.?#].[^\\s]*");
  QRegularExpressionMatch match = urlRegex.match(t_track);

  if (match.hasMatch())
  {
    m_PlayerMusic->play_streamed(t_track);
  }
  else
  {
    m_PlayerMusic->play(t_track);
  }
}

void AudioManager::PlaySFX(QString t_sfx)
{
  m_PlayerSFX->play_effect(t_sfx);
}

void AudioManager::PlaySFXCharacter(QString t_sfx, QString t_character)
{
  m_PlayerSFX->play_character_effect(t_character, t_sfx);
}
