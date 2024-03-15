#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <AOButton.h>
#include <QHash>

#include <modules/theme/widgets/dro_combo_box.h>
#include <modules/theme/widgets/dro_line_edit.h>
#include "modules/json/theme_reader.h"



class ThemeManager
{
public:
  ThemeManager(const ThemeManager&) = delete;

  static ThemeManager& get()
  {
    return s_Instance;
  }

  void LoadTheme(QString theme_name);
  void LoadGamemode(QString gamemode);


  //Data Management
  bool getConfigBool(QString value);
  bool getReloadPending();


  void toggleReload();



  //Widget Management
  void setResize(double size);
  double getResize();

  void addButton(QString name, AOButton* button);
  void refreshButtons();

  void addLineEdit(QString name, DROLineEdit* lineEdit);
  void refreshLineEdit();

  void addComboBox(QString name, DROComboBox* lineEdit);
  void refreshComboBox();

  ThemeReader mCurrentThemeReader = ThemeReader();

private:
  ThemeManager() {}
  static ThemeManager s_Instance;

  double mClientResize = 1;


  QHash<QString, AOButton*> mButtonWidgets { };
  QHash<QString, DROLineEdit*> mLineEditWidgets { };
  QHash<QString, DROComboBox*> mComboBoxWidgets { };

  bool mRequiresReload = true;
};

#endif // THEMEMANAGER_H
