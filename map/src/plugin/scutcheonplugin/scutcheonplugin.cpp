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

#include "scutcheonplugin.h"
#include "scutcheon.h"

ScutcheonPlugin::ScutcheonPlugin(QObject * parent)
    : QObject(parent)
{
}

QString ScutcheonPlugin::getname()
{
    return QStringLiteral("标牌显示插件");
}

bool ScutcheonPlugin::init()
{
    m_Scutcheon       = new Scutcheon;
    m_actionScutcheon = new QAction(QStringLiteral("显示标牌"));
    if (m_actionScutcheon)
    {
        connect(m_actionScutcheon, &QAction::triggered, this, &ScutcheonPlugin::addScutcheon);
        IPluginView::getInstance().registerAction(QStringLiteral("视图"), QStringLiteral("显示"), m_actionScutcheon);
    }
    return true;
}

bool ScutcheonPlugin::clean()
{
    return true;
}

void ScutcheonPlugin::addScutcheon()
{
    if (m_Scutcheon)
    {
        osg::ref_ptr<osg::Node> node = m_Scutcheon->createScucheon();
        NodeModule::getInstance()->addChildNode(node);
    }
}
