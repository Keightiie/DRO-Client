#pragma once

#include "mk2/spriteviewer.h"
#include <QMap>

class AOApplication;

class DRStickerViewer : public mk2::SpriteViewer
{
  Q_OBJECT

public:
  explicit DRStickerViewer(AOApplication *ao_app, QWidget *parent = nullptr);
  ~DRStickerViewer();

  void set_hide_when_done(bool enabled);

  void set_theme_image(QString p_file_name, QString p_character);

  void set_theme_image(QString p_file_name);

  void set_chatbox_image(QString p_chatbox_name, bool p_is_self, bool chatmessage_is_empty, QString pair);

  void set_variable_map(QMap<QString, QString> t_map);

  void set_variable_string(QString t_path);

  QString getVariableString();
  QMap<QString, QString> getVariableMap();

private:
  AOApplication *ao_app = nullptr;

  bool m_hide_when_done;
  QString mFallbackImage = "";
  QString mVariableString = "";
  QMap<QString, QString> mVariables = {};

private slots:
  void maybe_hide();
};
