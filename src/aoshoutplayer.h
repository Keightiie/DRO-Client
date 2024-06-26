#ifndef AOSHOUTPLAYER_H
#define AOSHOUTPLAYER_H

#include "aoobject.h"

class AOShoutPlayer : public AOObject
{
  Q_OBJECT

public:
  AOShoutPlayer(AOApplication *p_ao_app, QObject *p_parent = nullptr);

  void play(QString character, QString shout);
};

#endif // AOSHOUTPLAYER_H
