#include "shopitemstock.h"
#include "AOApplication.h"
#include "commondefs.h"
#include "file_functions.h"
#include <QRandomGenerator>

#include <modules/theme/thememanager.h>

#include <modules/managers/april_fools_manager.h>

ShopItemStock::ShopItemStock(QWidget *parent)
    : QWidget{parent}
{
  p_itemBackground = new AOButton(this, AOApplication::getInstance());
  ThemeManager::get().ResizeWidget(p_itemBackground, 138, 200);

  p_itemIcon = new AOImageDisplay(this, AOApplication::getInstance());
  ThemeManager::get().ResizeWidget(p_itemIcon, 60, 60);
  ThemeManager::get().TranslatePosition(p_itemIcon, 39, 70);
  p_itemIcon->set_theme_image("char_locked.png");


  p_Price = new DRTextEdit(p_itemBackground);


  //Message Text
  p_Price->setFrameStyle(QFrame::NoFrame);
  ThemeManager::get().TranslatePosition(p_Price, 40, 161);
  ThemeManager::get().ResizeWidget(p_Price, 85, 30);

  p_Price->setReadOnly(true);
  set_drtextedit_font(p_Price, "AF24_monocoin_shop", COURTROOM_FONTS_INI, AOApplication::getInstance());
  p_Price->setPlainText(p_Price->toPlainText());


  connect(p_itemBackground, SIGNAL(clicked()), this, SLOT(PurchaseStock()));
}

void ShopItemStock::SetStock(AF24Shop t_itemType, QString t_itemName)
{
  if(t_itemType == Character)
  {
    const QString l_icon_path = AOApplication::getInstance()->get_character_path(t_itemName, "char_icon.png");
    if(file_exists(l_icon_path))
    {
      p_itemIcon->set_image(l_icon_path);
    }
    p_itemIcon->show();
    m_price = QRandomGenerator::global()->bounded(5, 21);

    p_itemBackground->set_theme_image("item_shop", "shop/item_base.png", "courtroom", "N/A");
    p_Price->setPlainText(QString::number(m_price));
  }

  if(t_itemType == OutOfStock)
  {
    p_itemIcon->hide();
    p_itemBackground->set_theme_image("item_shop", "shop/item_oos.png", "courtroom", "N/A");
    p_Price->setPlainText("");
  }
  m_itemType = t_itemType;
  m_itemName = t_itemName;
}

void ShopItemStock::PurchaseStock()
{
  if(m_itemType == OutOfStock) return;

  if(AprilFoolsManager::get().subtractMonocoins(m_price))
  {
    AprilFoolsManager::get().UnlockCharacter(m_itemName);
    AprilFoolsManager::get().UnlockAchivement(PURCHASE);
    SetStock(OutOfStock, "N/A");
  }
}
