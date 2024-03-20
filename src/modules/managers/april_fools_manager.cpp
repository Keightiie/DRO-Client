#include "april_fools_manager.h"
#include "commondefs.h"

#include "../theme/thememanager.h"
#include <AOApplication.h>
#include <optional>
#include <qcolor.h>
#include "courtroom.h"
#include "drtheme.h"
#include "QTimer"


AprilFoolsManager AprilFoolsManager::s_Instance;

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
}
