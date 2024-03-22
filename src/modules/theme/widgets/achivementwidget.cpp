#include "achivementwidget.h"
#include "AOApplication.h"
#include "commondefs.h"
#include "file_functions.h"
#include "modules/theme/thememanager.h"

AchivementWidget::AchivementWidget(QWidget *parent)
    : QWidget{parent}
{
  AOApplication *ao_app = AOApplication::getInstance();

  pBackgroundImage = new DRStickerViewer(ao_app, this);
  p_AchivementName = new DRTextEdit(pBackgroundImage);


  p_AchivementIcon = new AOImageDisplay(this, ao_app);

  ThemeSetup();
  hide();
}

void AchivementWidget::SetAchivement(AF24Achivements t_achivement)
{
  if(m_AchivementNames.contains(t_achivement))
  {
    p_AchivementName->setPlainText(m_AchivementNames[t_achivement]);
  }
  if(m_AchivementIcons.contains(t_achivement))
  {
    p_AchivementIcon->set_theme_image(m_AchivementIcons[t_achivement]);
  }
  else
  {
    p_AchivementIcon->set_theme_image("achivements/placeholder.png");
  }
  show();
  QTimer::singleShot(2500, this, SLOT(AchivementDone()));
}

void AchivementWidget::ThemeSetup()
{

  //Gather Global Variables
  AOApplication *lAOApp = AOApplication::getInstance();

  //Setup the achivemente "frame"
  pBackgroundImage->move(0, 0);
  ThemeManager::get().ResizeWidget(pBackgroundImage, 222, 51);

  if (!lAOApp->find_theme_asset_path("achivement_base", animated_or_static_extensions()).isEmpty())
    pBackgroundImage->set_theme_image("achivement_base");

  set_sticker_play_once(pBackgroundImage, "achivement_base", COURTROOM_CONFIG_INI, lAOApp);

  //Message Text
  p_AchivementName->setFrameStyle(QFrame::NoFrame);
  ThemeManager::get().TranslatePosition(p_AchivementName, 42, 9);
  ThemeManager::get().ResizeWidget(p_AchivementName, 250, 20);

  p_AchivementName->setReadOnly(true);
  set_drtextedit_font(p_AchivementName, "AF24_achivement_popup", COURTROOM_FONTS_INI, lAOApp);
  p_AchivementName->setPlainText(p_AchivementName->toPlainText());

  //Icon
  ThemeManager::get().TranslatePosition(p_AchivementIcon, 8, 11);
  ThemeManager::get().ResizeWidget(p_AchivementIcon, 35, 35);
  p_AchivementIcon->set_theme_image("achivements/placeholder.png");
  p_AchivementIcon->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void AchivementWidget::AchivementDone()
{
  hide();
}
