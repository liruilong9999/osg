#include <QDebug>
#include <lib/appskeleton/ipluginview.h>
#include "gridctrlplugin.h"
#include "gridctrl.h"

GridCtrlPlugin::GridCtrlPlugin(QObject * parent)
    : QObject(parent)
{
    m_action = new QAction(QStringLiteral("显示网格"), this);
    m_grid   = new GridCtrl;
}

QString GridCtrlPlugin::getname()
{
    return QStringLiteral("网格显示插件");
}

bool GridCtrlPlugin::init()
{
    connect(m_action, &QAction::triggered, this, &GridCtrlPlugin::gridSlots);
    IPluginView::getInstance().registerAction(QStringLiteral("视图"), QStringLiteral("界面显示"), m_action);
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
