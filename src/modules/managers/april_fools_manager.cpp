#include "april_fools_manager.h"
#include "character_manager.h"
#include "commondefs.h"

#include "../theme/thememanager.h"
#include <AOApplication.h>
#include <optional>
#include <qcolor.h>
#include "aosystemplayer.h"
#include "courtroom.h"
#include "drtheme.h"
#include "QTimer"
#include "QRandomGenerator"
#include "commondefs.h"


AprilFoolsManager AprilFoolsManager::s_Instance;



void AprilFoolsManager::LoadSave()
{

  QStringList l_saveData = CharacterManager::get().LoadAFList(AF24_SAVE);
  if(l_saveData.count() < 3)
  {
    return;
  }
  m_UnlockedCharacters = fromBase64<QStringList>(l_saveData[0]);
  m_AchivementUnlocked = fromBase64<QHash<AF24Achivements, bool>>(l_saveData[1]);
  m_MonocoinCount = fromBase64<int>(l_saveData[2]);

}

void AprilFoolsManager::Save()
{
  QStringList l_achivements = {};
  l_achivements.append(toBase64(m_UnlockedCharacters));
  l_achivements.append(toBase64(m_AchivementUnlocked));
  l_achivements.append(toBase64(m_MonocoinCount));


  CharacterManager::get().SaveAFList(AF24_SAVE, l_achivements);
}

QString AprilFoolsManager::UnlockCharacter()
{
  return "";
}

void AprilFoolsManager::GachaPull()
{

}

void AprilFoolsManager::UnlockCharacter(QString t_character)
{
  if(m_UnlockedCharacters.contains(t_character)) return;
  m_UnlockedCharacters.append(t_character);

  for (auto it = m_CharacterUnlockConditions.constBegin(); it != m_CharacterUnlockConditions.constEnd(); ++it)
  {
    if (it.value().contains(t_character))
    {
      bool l_allCharsUnlocked = true;
      for (const QString &character : it.value())
      {
        if (!m_UnlockedCharacters.contains(character)) l_allCharsUnlocked = false;
      }

      if(l_allCharsUnlocked)
      {
        AprilFoolsManager::get().UnlockAchivement(it.key());
      }
    }
  }

  Save();
}


QString AprilFoolsManager::RandomCharacter(QStringList t_characterList, bool t_unique)
{
  if (t_characterList.isEmpty())
    return QString(); // Return an empty string if the list is empty


  QStringList characterList = t_characterList;
  characterList.removeDuplicates();

  for(QString l_chara : m_UnlockedCharacters)
  {
    if(characterList.contains(l_chara))
    {
      if(t_unique) characterList.removeAll(l_chara);
    }
  }

  int randomIndex = QRandomGenerator::global()->bounded(characterList.size());
  return characterList[randomIndex];
}

bool AprilFoolsManager::isCharacterUnlocked(QString t_character)
{
  return m_UnlockedCharacters.contains(t_character);
}

int AprilFoolsManager::getMonocoinCount()
{
  return m_MonocoinCount;
}

void AprilFoolsManager::addMonocoins(int t_count)
{
  m_MonocoinCount += t_count;
  updateMonocoinDisplay();
}

bool AprilFoolsManager::subtractMonocoins(int t_count)
{
  if(m_MonocoinCount - t_count < 0) return false;
  m_MonocoinCount -= t_count;
  updateMonocoinDisplay();
  return true;
}

void AprilFoolsManager::updateMonocoinDisplay()
{
  std::optional<QColor> l_color;
  bool is_bold = false;

  AOApplication *l_AOApp = AOApplication::getInstance();

  if(l_AOApp->current_theme->m_jsonLoaded)
  {
    widgetFontStruct fontstruct = ThemeManager::get().mCurrentThemeReader.getFont(COURTROOM, "AF24_monocoin_text");
    l_color = fontstruct.color;
    is_bold = fontstruct.bold;
  }

  l_AOApp->m_courtroom->p_AF24MonocoinText->ensurePolished();
  QTextCharFormat formatting = QTextCharFormat();

  if(l_color.has_value())
  {
    formatting.setForeground(l_color.value());
  }

  if (is_bold) formatting.setFontWeight(QFont::Bold);

  l_AOApp->m_courtroom->p_AF24MonocoinText->clear();
  QTextCursor l_cursor = l_AOApp->m_courtroom->p_AF24MonocoinText->textCursor();
  l_cursor.insertText("x" + QString::number(m_MonocoinCount), formatting);
  l_AOApp->m_courtroom->pShopMenu->UpdateMonocoins(m_MonocoinCount);
}

void AprilFoolsManager::UnlockAchivement(AF24Achivements t_achivement)
{
  if(m_AchivementUnlocked.contains(t_achivement)) return;
  m_AchivementUnlocked[t_achivement] = true;

  AOApplication *l_AOApp = AOApplication::getInstance();
  if(p_AchivementPopup != nullptr) p_AchivementPopup->SetAchivement(t_achivement);
  if(m_AchivementMonocoins.contains(t_achivement))
  {
    addMonocoins(m_AchivementMonocoins[t_achivement]);
  }
  else
  {
    addMonocoins(10);
  }
  l_AOApp->m_courtroom->m_system_player->play(l_AOApp->get_sfx("achivement"));
}

void AprilFoolsManager::SetupAchivement(AchivementWidget *t_widget)
{
  p_AchivementPopup = t_widget;
}


template<typename T>
QString AprilFoolsManager::toBase64(const T& data) {
  QByteArray byteArray;
  QDataStream stream(&byteArray, QIODevice::WriteOnly);
  stream << data;

  QByteArray base64Data = byteArray.toBase64();
  return QString(base64Data);
}

template<typename T>
T AprilFoolsManager::fromBase64(const QString& base64String) {
  QByteArray byteArray = QByteArray::fromBase64(base64String.toUtf8());
  QDataStream stream(&byteArray, QIODevice::ReadOnly);

  T data;
  stream >> data;

  return data;
}
