#ifndef LOBBY_H
#define LOBBY_H

#include "aobutton.h"
#include "aoconfig.h"
#include "aoimagedisplay.h"
#include "aopacket.h"
#include "aotextarea.h"
#include "drtextedit.h"

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QTextBrowser>

class AOApplication;

class Lobby : public QMainWindow
{
  Q_OBJECT

public:
  Lobby(AOApplication *p_ao_app);

  void set_widgets();
  void list_servers();
  void list_favorites();
  void append_chatmessage(QString f_name, QString f_message);
  void append_error(QString f_message);
  void set_choose_a_server();
  void set_player_count(int players_online, int max_players);
  void set_loading_text(QString p_text);
  void set_stylesheet(QWidget *widget, QString target_tag);
  void set_stylesheets();
  void set_fonts();
  void show_loading_overlay();
  void hide_loading_overlay();
  int get_selected_server();

  void set_loading_value(int p_value);

  bool public_servers_selected = true;

private:
  static const QString INI_DESIGN;
  static const QString INI_FONTS;

  AOApplication *ao_app = nullptr;
  AOConfig *ao_config = nullptr;

  AOImageDisplay *ui_background = nullptr;

  AOButton *ui_public_servers = nullptr;
  AOButton *ui_favorites = nullptr;

  AOButton *ui_refresh = nullptr;
  AOButton *ui_add_to_fav = nullptr;
  AOButton *ui_connect = nullptr;

  DRTextEdit *ui_version = nullptr;
  AOButton *ui_about = nullptr;

  QListWidget *ui_server_list = nullptr;

  DRTextEdit *ui_player_count = nullptr;
  AOTextArea *ui_description = nullptr;

  AOTextArea *ui_chatbox = nullptr;

  QLineEdit *ui_chatname = nullptr;
  QLineEdit *ui_chatmessage = nullptr;

  AOImageDisplay *ui_loading_background = nullptr;
  DRTextEdit *ui_loading_text = nullptr;
  QProgressBar *ui_progress_bar = nullptr;
  AOButton *ui_cancel = nullptr;

  server_type f_last_server;

private slots:
  void on_public_servers_clicked();
  void on_favorites_clicked();

  void on_refresh_pressed();
  void on_refresh_released();
  void on_add_to_fav_pressed();
  void on_add_to_fav_released();
  void on_connect_pressed();
  void on_connect_released();
  void on_about_clicked();
  void on_server_list_clicked(QModelIndex p_model);
  void on_chatfield_return_pressed();
};

#endif // LOBBY_H
