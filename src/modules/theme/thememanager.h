#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QHash>
#include <aobutton.h>
#include <aoimagedisplay.h>

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

  //Tabs
  void createTabParent();
  void execLayerTabs();
  void resetSelectedTabs();
  void toggleTab(QString t_tabName, QString t_tabGroup);
  void detatchTab(QString t_tabName);
  QVector <ThemeTabInfo> getTabsInfo();


  void execRemoveWidget(QString t_name);

  void loadTheme(QString theme_name);
  void LoadGamemode(QString gamemode);

  void setWidgetPosition(QWidget *t_widget, int x, int y);
  void setWidgetDimensions(QWidget *t_widget, int t_width, int t_height);
  void autoWidgetDimensions(QWidget *t_widget, QString t_name, ThemeSceneType t_scene);

  //Widgets
  void SetWidgetNames(QHash<QString, QWidget *> t_WidgetNames);
  void addWidgetName(QString t_widgetName, QWidget *t_widget);

  //Tabs


  //Data Management
  bool getConfigBool(QString value);
  bool getReloadPending();
  void toggleReload();

  //Widget Management
  pos_size_type resizePosition(pos_size_type t_position, double t_scale);

  void setResize(double size);
  double getResize();
  void setViewporResize(double size);
  double getViewporResize();

  void addButton(QString name, AOButton* button);
  void refreshButtons();

  void addLineEdit(QString name, DROLineEdit* lineEdit);
  void addComboBox(QString name, DROComboBox* lineEdit);
  void refreshLineEdit();
  void refreshComboBox();

  void setCourtroomBackground(AOImageDisplay *t_background);

  template<typename T>
  T* getWidgetType(QString t_name)
  {
    QWidget *mReturnWidget = ThemeManager::get().getWidget(t_name);
    if (dynamic_cast<T*>(mReturnWidget) != nullptr)
    {
      T* l_return = dynamic_cast<T*>(mReturnWidget);
      return l_return;
    }

    return nullptr;
  }

  QWidget *getWidget(QString name);
  AOButton *GetButton(QString t_name);

  ThemeReader mCurrentThemeReader = ThemeReader();


  //Create Widgets
  void clearWidgets();
  void createButtonWidget(QString t_name, QWidget *t_parent = nullptr);
  void createImageWidget(QString t_name, QString t_image, bool visible, QWidget *t_parent = nullptr);
  void createComboboxWidget(QString t_name);

private:
  ThemeManager() {}
  static ThemeManager s_Instance;

  double mClientResize = 1;

  double mViewportResize = 1;


  QMap<QString, QWidget *> waTabWidgets = {};

  QHash<QString, QWidget *> m_WidgetNames = {};
  QHash<QString, AOButton*> mButtonWidgets { };
  QHash<QString, DROLineEdit*> mLineEditWidgets { };
  QHash<QString, DROComboBox*> mComboBoxWidgets { };

  bool mRequiresReload = true;
  AOImageDisplay *wCourtroomBackground = nullptr;
};

#endif // THEMEMANAGER_H
