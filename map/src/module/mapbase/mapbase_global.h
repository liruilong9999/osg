#ifndef FEATUREMODULE_GLOBAL_H
#define FEATUREMODULE_GLOBAL_H
#include <QtCore/qglobal.h>

#if defined(MAPBASE_LIBRARY)
#define MAPBASE_EXPORT Q_DECL_EXPORT
#else
#define MAPBASE_EXPORT Q_DECL_IMPORT
#endif
#endif
