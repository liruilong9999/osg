#include <QDebug>
#include <lib/appskeleton/appskeleton.h>
#include <lib/appskeleton/ipluginview.h>
#include <module/mapmodule/mapmodule.h>
#include <module/modelmodule/modelmodule.h>
#include <module/nodemodule/nodemodule.h>
#include "earthwidgetplugin.h"
#include "earthwidget.h"

EarthWidgetPlugin::EarthWidgetPlugin(QObject * parent)
    : QObject(parent)
{
    m_earthWidget     = new EarthWidget;
    m_addHeightAction = new QAction(QStringLiteral("添加高程数据"));
    IPluginView::getInstance().getMainWindow()->getLayout()->addWidget(m_earthWidget);
}

QString EarthWidgetPlugin::getname()
{
    return QStringLiteral("地图显示插件");
}

bool EarthWidgetPlugin::init()
{
    if (m_addHeightAction)
    {
        connect(m_addHeightAction, &QAction::triggered, this, &EarthWidgetPlugin::addHeight);
        IPluginView::getInstance().registerAction(QStringLiteral("地图"), QStringLiteral("高程"), m_addHeightAction);
    }
    return true;
}

bool EarthWidgetPlugin::clean()
{
    return true;
}

void EarthWidgetPlugin::addHeight()
{
    m_actHeightClicked = !m_actHeightClicked;
    if (m_actHeightClicked)
    {
        osg::Node * node = MapModule::getInstance()->addHeight();
        NodeModule::getInstance()->getRootNode()->addChild(node);
    }
    else
    {
    }
}
