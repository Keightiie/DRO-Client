#include "droconfig.h"
#include "config/player_config.h"
#include "ui_droconfig.h"
#include "config/tabs/config_tab_graphics.h"
#include <QDebug>

DROConfig::DROConfig(QWidget *parent) : QMainWindow(parent), ui(new Ui::DROConfig)
{
  ui->setupUi(this);
  LOADED_CONFIG_DRO.loadConfig();
  CreateTabs();
}

DROConfig::~DROConfig()
{
  delete ui;
}

void DROConfig::CreateTabs()
{
  m_DROTabs.clear();

  m_DROTabs["OpenGL"] = new ConfigTabGraphics();

  ui->ConfigCategoryList->addItems(m_TabCategories.keys());
}

void DROConfig::SwitchCategory(QString l_Category)
{
  ui->ConfigTabWidget->clear();

  for(QString r_TabName : m_TabCategories[l_Category])
  {
    ui->ConfigTabWidget->addTab(m_DROTabs[r_TabName], r_TabName);
  }
}

void DROConfig::on_ConfigCategoryList_currentTextChanged(const QString &currentText)
{
  SwitchCategory(currentText);
}


void DROConfig::on_BtnSaveConfig_clicked()
{
  LOADED_CONFIG_DRO.saveConfig();
}


void DROConfig::on_pushButton_clicked()
{
  this->hide();
}

