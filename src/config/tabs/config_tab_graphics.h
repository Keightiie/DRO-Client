#ifndef CONFIG_TAB_GRAPHICS_H
#define CONFIG_TAB_GRAPHICS_H

#include <QWidget>

namespace Ui
{
class ConfigTabGraphics;
}

class ConfigTabGraphics : public QWidget
{
  Q_OBJECT

public:
  explicit ConfigTabGraphics(QWidget *parent = nullptr);
  ~ConfigTabGraphics();

private:
  Ui::ConfigTabGraphics *ui;
};

#endif // CONFIG_TAB_GRAPHICS_H
