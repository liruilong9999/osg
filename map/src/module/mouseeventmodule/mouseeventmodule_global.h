﻿#ifndef MOUSEEVENTMODULE_GLOBAL_H
#define MOUSEEVENTMODULE_GLOBAL_H
#include <QtCore/qglobal.h>

#if defined(MOUSEEVENTMODULE_LIBRARY)
#define MOUSEEVENTMODULE_EXPORT Q_DECL_EXPORT
#else
#define MOUSEEVENTMODULE_EXPORT Q_DECL_IMPORT
#endif
#endif
