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

private slots:
  void on_CheckboxUseGL_stateChanged(int arg1);

  void on_SpinFramesPerSecond_valueChanged(int arg1);

  void on_SwapSamples_valueChanged(int arg1);

  void on_SpinSwapInterval_valueChanged(int arg1);

  void on_SpinSamples_valueChanged(int arg1);

private:
  Ui::ConfigTabGraphics *ui;
};

#endif // CONFIG_TAB_GRAPHICS_H
