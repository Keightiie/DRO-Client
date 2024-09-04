#ifndef DROCONFIG_H
#define DROCONFIG_H

#include <QMainWindow>
#include <QMap>

namespace Ui
{
class DROConfig;
}

class DROConfig : public QMainWindow
{
  Q_OBJECT

public:
  explicit DROConfig(QWidget *parent = nullptr);
  ~DROConfig();

  void CreateTabs();
  void SwitchCategory(QString l_Category);

private slots:
  void on_ConfigCategoryList_currentTextChanged(const QString &currentText);

  void on_BtnSaveConfig_clicked();

  void on_pushButton_clicked();

private:
  Ui::DROConfig *ui;

  QMap<QString, QWidget*> m_DROTabs = {};
  QMap<QString, QStringList> m_TabCategories =
  {
    {"Graphics", {"OpenGL"}}
  };
};

#endif // DROCONFIG_H
