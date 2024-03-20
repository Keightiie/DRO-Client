#ifndef APRILFOOLSMANAGER_H
#define APRILFOOLSMANAGER_H

#include <qstringlist.h>



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
  bool isCharacterUnlocked(QString t_character);

  int getMonocoinCount();
  void addMonocoins(int t_count);
  bool subtractMonocoins(int t_count);
  void updateMonocoinDisplay();



private:
  AprilFoolsManager() {}
  static AprilFoolsManager s_Instance;

  int m_MonocoinCount = 100;
  QStringList m_UnlockedCharacters = {"Makoto_HD", "Hajime_HD", "Shuichi_HD", "Kaede Akamatsu_HD", "Shuichi Saihara_HD"};
};

#endif // APRILFOOLSMANAGER_H
