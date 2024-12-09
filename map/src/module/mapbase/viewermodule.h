#ifndef VIEWERMODULE_H
#define VIEWERMODULE_H
#include <QSharedPointer>
#include <osgViewer/Viewer>
#include <common/TSingleton.hpp>
#include "mapbase_global.h"

struct ViewerModulePrivate;
class MAPBASE_EXPORT ViewerModule : public TSingleton<ViewerModule>
{
    friend class TSingleton<ViewerModule>;

public:
    // 设置当前场景
    void setOsgViewer(osgViewer::Viewer * viewer);
    // 获取当前场景
    osgViewer::Viewer * getOsgViewer();
    // 设置地图节点

private:
    ViewerModule();
    QSharedPointer<ViewerModulePrivate> m_p;
};

#endif
