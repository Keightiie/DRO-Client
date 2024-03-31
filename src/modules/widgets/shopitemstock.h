#ifndef SHOPITEMSTOCK_H
#define SHOPITEMSTOCK_H

#include <QObject>
#include <QWidget>
#include <drtextedit.h>
#include "datatypes.h"
#include <AOButton.h>
#include <aoimagedisplay.h>

class ShopItemStock : public QWidget
{
  Q_OBJECT
public:
  explicit ShopItemStock(QWidget *parent = nullptr);
  void SetStock(AF24Shop t_itemType, QString t_itemName);

signals:

public slots:
  void PurchaseStock();

private:

  int m_price = 10;
  DRTextEdit *p_Price = nullptr;
  AOButton *p_itemBackground = nullptr;
  AOImageDisplay *p_itemIcon = nullptr;
  QString m_itemName = "Monokuma_HD";
  AF24Shop m_itemType = OutOfStock;

};

#endif // SHOPITEMSTOCK_H
