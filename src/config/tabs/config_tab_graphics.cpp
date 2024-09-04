#include "config_tab_graphics.h"
#include "config/player_config.h"
#include "ui_config_tab_graphics.h"

#include <QDebug>

ConfigTabGraphics::ConfigTabGraphics(QWidget *parent) : QWidget(parent), ui(new Ui::ConfigTabGraphics)
{
  ui->setupUi(this);
  ui->CheckboxUseGL->setChecked(LOADED_CONFIG_DRO.getBool("useOpenGL", true));
  ui->SpinFramesPerSecond->setValue(LOADED_CONFIG_DRO.getInt("gl_fps", 60));
  ui->SpinSamples->setValue(LOADED_CONFIG_DRO.getInt("gl_samples", 4));
  ui->SpinSwapInterval->setValue(LOADED_CONFIG_DRO.getInt("gl_swap", 0));
}

ConfigTabGraphics::~ConfigTabGraphics()
{
  delete ui;
}

void ConfigTabGraphics::on_CheckboxUseGL_stateChanged(int arg1)
{
  if(arg1 == Qt::CheckState::Checked)
  {
    LOADED_CONFIG_DRO.setBool("useOpenGL", true);
  }
  else
  {
    LOADED_CONFIG_DRO.setBool("useOpenGL", false);
  }
}


void ConfigTabGraphics::on_SpinFramesPerSecond_valueChanged(int arg1)
{
  LOADED_CONFIG_DRO.setInt("gl_fps", arg1);
}


void ConfigTabGraphics::on_SwapSamples_valueChanged(int arg1)
{
  LOADED_CONFIG_DRO.setInt("gl_samples", arg1);
}


void ConfigTabGraphics::on_SpinSwapInterval_valueChanged(int arg1)
{
  LOADED_CONFIG_DRO.setInt("gl_swap", arg1);
}


void ConfigTabGraphics::on_SpinSamples_valueChanged(int arg1)
{
  LOADED_CONFIG_DRO.setInt("gl_samples", arg1);
}

