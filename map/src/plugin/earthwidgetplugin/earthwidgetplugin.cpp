#include <QDebug>
#include <QGridLayout>
#include <iappskeleton/iappview.h>
#include <lbase/lbase.h>
#include <mapbase/mapbase.h>
#include "earthwidgetplugin.h"
#include "earthwidget.h"

EarthWidgetPlugin::EarthWidgetPlugin(QObject * parent)
    : QObject(parent)
{
    m_earthWidget = new EarthWidget;

}

QString EarthWidgetPlugin::getname()
{
    return QString("地图显示插件");
}

bool EarthWidgetPlugin::init()
{
    m_addHeightAction  = new QAction(QString("添加高程数据"));
    IAppView * baseObj = dynamic_cast<IAppView *>(ObjectRegistry::instance().getObject("IPluginView"));
    if (baseObj)
    {
        baseObj->getLayout()->addWidget(m_earthWidget);
    }
    if (m_addHeightAction)
    {
        connect(m_addHeightAction, &QAction::triggered, this, &EarthWidgetPlugin::addHeight);
        IAppView * baseObj = dynamic_cast<IAppView *>(ObjectRegistry::instance().getObject("IPluginView"));
		if(baseObj)
        {
            baseObj->registerAction(QString("地图"), QString("高程"), m_addHeightAction);
		}
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
