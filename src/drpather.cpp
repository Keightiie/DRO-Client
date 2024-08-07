#include "drpather.h"

#include <QCoreApplication>
#include <modules/managers/pathing_manager.h>
#include <QDir>

/* @brief Gets the directory containing the base folder and the application.
 *
 * This function is a system-independent QDir::currentPath() system-independent. The only edge case really is MacOS,
 * where due to the way applications are bundled, makes QDir::currentPath() return nonsensical values by default and
 * QCoreApplication::applicationDirPath() returns the directory to the internal executable of the bundle rather
 * than the bundle location itself.
 *
 * @return Directory.
 */
QString DRPather::GetApplicationPath()
{
#ifdef Q_OS_MACOS
  QDir l_mac_path(QCoreApplication::applicationDirPath());
  for (int i = 0; i < 3; ++i) // equivalent of "/../../.."
    l_mac_path.cdUp();
  return l_mac_path.canonicalPath();
#else
  return QDir::currentPath();
#endif
}

QString DRPather::GetBasePath(QString t_subpath)
{
  return GetApplicationPath() + "/base/" + t_subpath;
}

QString DRPather::SearchPathFirst(QString t_path)
{
  return PathingManager::get().searchFirstDirectory(t_path);
}

QStringList DRPather::SearchPathAll()
{
  return {};
}
