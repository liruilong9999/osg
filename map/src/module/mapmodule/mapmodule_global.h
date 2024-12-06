#ifndef MAPMODULE_GLOBAL_H
#define MAPMODULE_GLOBAL_H
#include <QtCore/qglobal.h>

#if defined(MAPMODULE_LIBRARY)
#define MAPMODULE_EXPORT Q_DECL_EXPORT
#else
#define MAPMODULE_EXPORT Q_DECL_IMPORT
#endif
#endif
