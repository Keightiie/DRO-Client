#ifndef PAIRMANAGER_H
#define PAIRMANAGER_H

#include <QSlider>
#include <QString>



class PairManager
{
public:
  PairManager(const PairManager&) = delete;

  static PairManager& get()
  {
    return s_Instance;
  }

  void SetSlider(QSlider *slider);

  bool GetUsePairData();
  void SetPairData(QString character, QString emote, int selfOffset, int pairOffset, bool flipped);
  double GetOffsetSelf();
  double GetOffsetOther();

  QString GetEmoteName();
  QString GetCharacterFolder();
  bool GetCharacterFlipped();

  void DisableUpcomingPair();

  void SetUserPair(int partner, int offset);
  bool GetCanPair();
  bool GetSpriteIsVisible();

private:
  PairManager() {}
  static PairManager s_Instance;

  bool mPairUsed = true;
  bool mIsFlipped = false;

  QString mCharacter = "DUMMY";
  QString mEmote = "DUMMY";
  int mSelfOffset = 0;
  int mPairOffset = 0;

  int mLocalPair = -1;
  int mLocalOffset = 0;

  QSlider *pSliderWidget = nullptr;
};

#endif // PAIRMANAGER_H
