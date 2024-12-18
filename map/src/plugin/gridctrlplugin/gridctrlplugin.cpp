#include <QDebug>
#include <iappskeleton/iappview.h>
#include <lbase/lbase.h>
#include "gridctrlplugin.h"
#include "gridctrl.h"

GridCtrlPlugin::GridCtrlPlugin(QObject * parent)
    : QObject(parent)
{
    m_action = new QAction(QString("显示网格"), this);
    m_grid   = new GridCtrl;
}

QString GridCtrlPlugin::getname()
{
    return QString("网格显示插件");
}

bool GridCtrlPlugin::init()
{
    connect(m_action, &QAction::triggered, this, &GridCtrlPlugin::gridSlots);
    IAppView * baseObj = dynamic_cast<IAppView *>(ObjectRegistry::instance().getObject("IPluginView"));
    if (baseObj)
    {
        baseObj->registerAction(QString("视图"), QString("界面显示"), m_action);
    }
    return true;
}

bool GridCtrlPlugin::clean()
{
    return true;
}

void GridCtrlPlugin::gridSlots()
{
    m_grid->showOrHideGrid();
}
