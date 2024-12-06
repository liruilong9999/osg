
#include <osg/Group>
#include <osgViewer/Viewer>

#include "viewermodule.h"

struct ViewerModulePrivate
{
    osgViewer::Viewer * viewer{nullptr}; // 当前场景
};

void ViewerModule::setOsgViewer(osgViewer::Viewer * viewer)
{
    if (m_p)
    {
        m_p->viewer = viewer;
    }
}

osgViewer::Viewer * ViewerModule::getOsgViewer()
{
    return m_p->viewer;
}

ViewerModule::ViewerModule()
{
    m_p.reset(new ViewerModulePrivate);
}
