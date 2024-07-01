#ifndef TAGGABLELINEEDIT_H
#define TAGGABLELINEEDIT_H

#include "qdebug.h"
#include <QTextEdit>
#include <QRegularExpression>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextImageFormat>

class TaggableLineEdit : public QTextEdit {
  Q_OBJECT

public:
  TaggableLineEdit(QWidget *parent = nullptr) : QTextEdit(parent)
  {
    setPlaceholderText("Say something in-character");
    connect(this, &QTextEdit::textChanged, this, &TaggableLineEdit::onTextChanged);
  }

protected:
  void onTextChanged()
  {

  }
};
#endif // TAGGABLELINEEDIT_H
