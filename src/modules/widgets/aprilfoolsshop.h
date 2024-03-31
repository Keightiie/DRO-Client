#ifndef APRILFOOLSSHOP_H
#define APRILFOOLSSHOP_H

#include "shopitemstock.h"

#include <QObject>
#include <QWidget>
#include <datatypes.h>
#include <aoimagedisplay.h>
#include <drtextedit.h>

class AprilFoolsShop : public QWidget
{
  Q_OBJECT
public:
  explicit AprilFoolsShop(QWidget *parent = nullptr);
  void CreateRow(int y);
  void CreateStock(int x, int y);

  void UpdateMonocoins(int t_count);

public slots:
  void RestockShop();

signals:

private:

  DRTextEdit *p_MonocoinCount = nullptr;
  QVector<ShopItemStock*> p_shopItems = {};
  AOImageDisplay *p_ShopBackground = nullptr;

};

#endif // APRILFOOLSSHOP_H
