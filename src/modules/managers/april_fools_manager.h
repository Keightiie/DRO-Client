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

  void LoadSave();
  void Save();

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

  QHash<AF24Achivements, QString> m_AchivementNames =
      {
          {WELCOME, "WELCOME TO DRO"},
          {NEKU, "Focus..."},
          {OTONOKOJI, "Otonokoji Twins"},
          {KINDERGARDEN, "Kindergarden"},
          {PURCHASE,"SHOPPING SPREE"},
          {PROTAGPARTY, "PROTAG PARTY"},
          {RAINBOW, "RAINBOW!!!"},
          {AKANE, "Akane^2"},
          {LEON, "11037"},
          {SEESAW, "Seesaw"},
          {JERM, "Jerm70"},
          {BESTIES, "Besties!"},
          {HEIGHT, "Height Difference"},
          {LUCKY, "Lucky!"},
          {PAT, "PAT RECEIVER"},
          {IMPOSTER, "Among Us"},
          {HAJIME, "Hajime^2"},
          {SISTERS, "Despair Sisters"},
          {DETECTIVES, "Master Detectives"},
          {ALTEREGO, "Alter Ego!"},
          {ZOO, "Zoo"},
          {MONOKUBS, "The Monokoubs"},
          {NAEGI, "Average Siblings"}
  };

  QHash<AF24Achivements, QString> m_AchivementIcons =
  {
          {WELCOME, "achivements/welcome.png"},
          {NEKU, "achivements/neku.png"},
          {OTONOKOJI, "achivements/otonokoji.png"},
          {KINDERGARDEN, "achivements/kindergarden.png"},
          {PURCHASE,"achivements/purchase.png"},
          {PROTAGPARTY, "achivements/protag.png"},
          {RAINBOW, "achivements/rainbow.png"},
          {AKANE, "achivements/akane.png"},
          {LEON, "achivements/leon.png"},
          {SEESAW, "achivements/seesaw.png"},
          {JERM, "achivements/jerm.png"},
          {BESTIES, "achivements/besties.png"},
          {HEIGHT, "achivements/height.png"},
          {LUCKY, "achivements/lucky.png"},
          {PAT, "achivements/pat.png"},
          {IMPOSTER, "achivements/imposter.png"},
          {HAJIME, "achivements/hajime.png"},
          {SISTERS, "achivements/sisters.png"},
          {ALTEREGO, "achivements/alterego.png"},
          {DETECTIVES, "achivements/detectives.png"},
          {ZOO, "achivements/zoo.png"},
          {MONOKUBS, "achivements/monokubs.png"},
          {NAEGI, "achivements/naegi.png"}
  };

  template<typename T>
  QString toBase64(const T& data);

  template<typename T>
  T fromBase64(const QString& base64String);

  QStringList StringListFromBase64(const QString &base64String);
private:
  QHash<AF24Achivements, bool> m_AchivementUnlocked = { };


  QHash<AF24Achivements, int> m_AchivementMonocoins = { {WELCOME, 10} };




  QHash<AF24Achivements, QStringList> m_CharacterUnlockConditions =
  {
          {PROTAGPARTY, {"Makoto_HD", "Hajime_HD", "Shuichi Saihara_HD", "Kaede Akamatsu_HD", "Komaru Naegi_HD"}},
          {KINDERGARDEN, {"Nagisa Shingetsu_HD", "Kotoko Utsugi_HD", "Jataro Kemuri_HD", "Monaca Towa_HD", "Masaru Daimon_HD"}},
          {NEKU, {"Neku Sakuraba_HD"}},
          {OTONOKOJI, {"Hibiki_HD", "Kanade_HD"}},
          {SISTERS, {"Junko_HD", "JunkoMM_HD"}},
          {SISTERS, {"Mukuro_HD", "JunkoMM_HD"}},
          {NAEGI, {"Makoto_HD", "Komaru Naegi_HD"}},
          {HEIGHT, {"Ryoma Hoshi_HD", "Gonta Gokuhara_HD"}},
          {DETECTIVES, {"Kirigiri_HD", "Shuichi Saihara_HD"}},
          {ALTEREGO, {"AlterEgo_HD", "Gonta AlterEgo_HD"}},
          {LUCKY, {"Makoto_HD", "Nagito_HD"}},
          {ZOO, {"Monotaro_HD", "Monosuke_HD", "Monodam_HD", "Monokid_HD", "Monophanie_HD"}},
          {MONOKUBS, {"Monotaro_HD", "Monosuke_HD", "Monodam_HD", "Monokid_HD", "Monophanie_HD", "Monomi_HD", "Shirokuma_HD", "Kurokuma_HD", "Usami_HD", "Monocrow_HD", "Monokuma_HD", "MonokumaV3_HD"}}
  };

  AprilFoolsManager() {}
  static AprilFoolsManager s_Instance;

  AchivementWidget *p_AchivementPopup = nullptr;

  int m_MonocoinCount = 9;
  QStringList m_UnlockedCharacters = {"Hifumi_HD"};
};

#endif // APRILFOOLSMANAGER_H
