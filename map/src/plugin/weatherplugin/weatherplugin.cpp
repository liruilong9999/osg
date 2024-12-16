#include <QDebug>
#include <lib/appskeleton/ipluginview.h>
#include <QAction>
#include <QLabel>
#include <QStatusBar>
#include <osgEarth/MapNode>
#include <osgViewer/Viewer>

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>
#include <module/layermodule/layermodule.h>
#include <module/mapmodule/mapmodule.h>
#include <lib/leventbus/leventbus.h>
#include <lib/llog/llog.h>

#include "weatherplugin.h"
#include "weather.h"

WeatherPlugin::WeatherPlugin(QObject * parent)
    : QObject(parent)
{
}

QString WeatherPlugin::getname()
{
    return QStringLiteral("模型生成插件");
}

bool WeatherPlugin::init()
{
    m_Weather       = new Weather;
    m_actionWeather = new QAction(QStringLiteral("添加日月星辰"));
    if (m_actionWeather)
    {
        connect(m_actionWeather, &QAction::triggered, this, &WeatherPlugin::addWeather);
        IPluginView::getInstance().registerAction(QStringLiteral("视图"), QStringLiteral("天气天候"), m_actionWeather);
    }
    return true;
}

bool WeatherPlugin::clean()
{
    return true;
}

void WeatherPlugin::addWeather()
{
    if (m_Weather)
    {
        osgEarth::Extension * node =
            m_Weather->addStars();
        osg::ref_ptr<osgEarth::MapNode> mapNode = NodeModule::getInstance()->getRootMapNode();
        mapNode->addExtension(node);
    }
}
