#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include <QString>
#include <QStringList>
#include <QVector>

QStringList animated_or_static_extensions();
QStringList animated_extensions();
QStringList audio_extensions();

bool file_exists(QString file_path);
bool dir_exists(QString file_path);

#endif // FILE_FUNCTIONS_H
