#ifndef NODEMODULE_GLOBAL_H
#define NODEMODULE_GLOBAL_H
#include <QtCore/qglobal.h>

#if defined(NODEMODULE_LIBRARY)
#define NODEMODULE_EXPORT Q_DECL_EXPORT
#else
#define NODEMODULE_EXPORT Q_DECL_IMPORT
#endif
#endif
