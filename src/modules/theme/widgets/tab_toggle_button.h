#ifndef TABTOGGLEBUTTON_H
#define TABTOGGLEBUTTON_H

#include <aobutton.h>

class TabToggleButton : public AOButton
{
  Q_OBJECT
public:
  TabToggleButton(QWidget *parent, AOApplication *p_ao_app);


  void refreshButtonStatus();
  void setTabName(QString t_name);
  void setTabGroup(QString t_name);
  void setActiveStatus(bool t_isActive);

signals:
  void tabClicked(TabToggleButton *emote_number);

private slots:
  void on_clicked();
  void displayContextMenu(QPoint t_position);
  void detatchTab();

private:
  QString mTabName = "";
  QString mTabGroup = "default";
  bool mTabActive = false;
  bool mIsDetatched = false;

};

#endif // TABTOGGLEBUTTON_H
