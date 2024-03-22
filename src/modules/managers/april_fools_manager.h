#ifndef APRILFOOLSMANAGER_H
#define APRILFOOLSMANAGER_H

#include "modules/theme/widgets/achivementwidget.h"
#include <QHash>
#include <qstringlist.h>
#include <datatypes.h>



class AprilFoolsManager
{
public:
  AprilFoolsManager(const AprilFoolsManager&) = delete;

  static AprilFoolsManager& get()
  {
    return s_Instance;
  }

  QString UnlockCharacter();
  void GachaPull();
  void UnlockCharacter(QString t_character);
  QString RandomCharacter(QStringList t_characterList, bool t_unique);
  bool isCharacterUnlocked(QString t_character);

  int getMonocoinCount();
  void addMonocoins(int t_count);
  bool subtractMonocoins(int t_count);
  void updateMonocoinDisplay();

  void UnlockAchivement(AF24Achivements t_achivement);
  void SetupAchivement(AchivementWidget *t_widget);



private:
  QHash<AF24Achivements, int> m_AchivementMonocoins =
  {
    {WELCOME, 10}

  };

  QHash<AF24Achivements, bool> m_AchivementUnlocked = { };

  AprilFoolsManager() {}
  static AprilFoolsManager s_Instance;

  AchivementWidget *p_AchivementPopup = nullptr;

  int m_MonocoinCount = 9;
  QStringList m_UnlockedCharacters = {"Hifumi_HD"};
};

#endif // APRILFOOLSMANAGER_H
