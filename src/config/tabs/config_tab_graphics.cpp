#include "config_tab_graphics.h"
#include "ui_config_tab_graphics.h"

ConfigTabGraphics::ConfigTabGraphics(QWidget *parent) : QWidget(parent), ui(new Ui::ConfigTabGraphics)
{
  ui->setupUi(this);
}

ConfigTabGraphics::~ConfigTabGraphics()
{
  delete ui;
}
