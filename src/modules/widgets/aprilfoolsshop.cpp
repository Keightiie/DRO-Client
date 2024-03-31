#include "aprilfoolsshop.h"
#include "AOApplication.h"


#include <modules/theme/thememanager.h>
#include "commondefs.h"
#include "modules/managers/april_fools_manager.h"
#include <modules/managers/character_manager.h>

AprilFoolsShop::AprilFoolsShop(QWidget *parent)
    : QWidget{parent}
{

  p_ShopBackground = new AOImageDisplay(this, AOApplication::getInstance());

  p_MonocoinCount = new DRTextEdit(p_ShopBackground);
  ThemeManager::get().ResizeWidget(p_ShopBackground, 960, 544);
  p_ShopBackground->set_theme_image("shop/background.png");

  p_shopItems = {};


  //Message Text
  p_MonocoinCount->setFrameStyle(QFrame::NoFrame);
  ThemeManager::get().TranslatePosition(p_MonocoinCount, 740, 8);
  ThemeManager::get().ResizeWidget(p_MonocoinCount, 120, 40);

  p_MonocoinCount->setReadOnly(true);
  set_drtextedit_font(p_MonocoinCount, "AF24_monocoin_shop", COURTROOM_FONTS_INI, AOApplication::getInstance());
  p_MonocoinCount->setPlainText(p_MonocoinCount->toPlainText());

  CreateRow(64);
  CreateRow(304);


}

void AprilFoolsShop::CreateRow(int y)
{
  CreateStock(90, y);
  CreateStock(250, y);
  CreateStock(410, y);
  CreateStock(570, y);
  CreateStock(730, y);
}

void AprilFoolsShop::CreateStock(int x, int y)
{
  ShopItemStock *l_newStock = new ShopItemStock(this);
  ThemeManager::get().TranslatePosition(l_newStock, x, y);
  p_shopItems.append(l_newStock);
}

void AprilFoolsShop::RestockShop()
{
  AprilFoolsManager::get().addMonocoins(5);
  for(ShopItemStock *l_stock : p_shopItems)
  {
    QString l_characterName = AprilFoolsManager::get().RandomCharacter(CharacterManager::get().GetServerCharacterNames(), true);
    l_stock->SetStock(Character, l_characterName);
  }

  QTimer::singleShot(60000, this, SLOT(RestockShop()));


}

void AprilFoolsShop::UpdateMonocoins(int t_count)
{
  p_MonocoinCount->setPlainText(QString::number(t_count));
}
