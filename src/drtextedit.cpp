#include "drtextedit.h"
#include "debug_functions.h"

#include <QDebug>
#include <QTextBlock>

DRTextEdit::DRTextEdit(QWidget *parent) : QTextEdit(parent)
{
  connect(this, SIGNAL(textChanged()), this, SLOT(on_text_changed()));
}

void DRTextEdit::set_outline(bool p_outline)
{
  QTextCharFormat widget_format = currentCharFormat();
  if (p_outline)
    widget_format.setTextOutline(QPen(Qt::black, 1));
  else
    widget_format.setTextOutline(Qt::NoPen);
  setCurrentCharFormat(widget_format);
  this->m_outline = p_outline;
}

bool DRTextEdit::get_outline()
{
  return this->m_outline;
}

void DRTextEdit::set_vertical_alignment(Qt::Alignment p_align)
{
  switch (p_align)
  {
  case Qt::AlignTop:
  case Qt::AlignVCenter:
  case Qt::AlignBottom:
    break;
  default:
    set_vertical_alignment(Qt::AlignTop);
    return;
  }
  m_valign = p_align;
  on_text_changed();
}

Qt::Alignment DRTextEdit::get_vertical_alignment()
{
  return this->m_valign;
}

void DRTextEdit::set_horizontal_alignment(Qt::Alignment p_align)
{
  switch (p_align)
  {
  case Qt::AlignLeft:
  case Qt::AlignHCenter:
  case Qt::AlignRight:
    break;
  default:
    set_horizontal_alignment(Qt::AlignLeft);
    return;
  }
  m_halign = p_align;
  on_text_changed();
}

Qt::Alignment DRTextEdit::get_horizontal_alignment()
{
  return this->m_halign;
}

void DRTextEdit::on_text_changed()
{
  if (m_status == Status::InProgress)
    return;
  m_status = Status::InProgress;

  refresh_horizontal_alignment();
  refresh_vertical_alignment();

  // we're done
  m_status = Status::Done;
}

void DRTextEdit::refresh_horizontal_alignment()
{
  // Do computations to align text horizontally
  setAlignment(m_halign);
}

void DRTextEdit::refresh_vertical_alignment()
{
  // This stores the total height of the totality of the text saved.
  int new_text_height = document()->size().height();
  if (document()->toPlainText().isEmpty())
  {
    // Qt is very special and does not set this to 0 for empty documents.
    new_text_height = 0;
  }
  // If we have not changed the document height since the last time the text was updated
  // We do not need to update anything, so we exit early.
  if (new_text_height == current_document_height)
    return;

  current_document_height = new_text_height;

  // The way we will simulate vertical alignment is by adjusting the top margin to simulate
  // center alignment, or bottom alignment.
  int top_margin = 0;
  switch (m_valign)
  {
  case Qt::AlignVCenter:
    top_margin = (height() - new_text_height) / 2;
    break;
  case Qt::AlignBottom:
    top_margin = (height() - new_text_height);
    break;
  default:
    break;
  }
  setViewportMargins(0, top_margin, 0, 0);
}
