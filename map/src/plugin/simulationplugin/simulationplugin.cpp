#include <QDebug>
#include <lib/appskeleton/ipluginview.h>
#include <QAction>

#include "simulationplugin.h"

SimulationPlugin::SimulationPlugin(QObject * parent)
    : QObject(parent)
{
    m_actionBuildModel  = new QAction(QStringLiteral("开始仿真"), this);
    m_actionRemoveModel = new QAction(QStringLiteral("结束仿真"), this);
    m_timer             = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimulationPlugin::simulationSlot);
}

QString SimulationPlugin::getname()
{
    return QStringLiteral("模型生成插件");
}

bool SimulationPlugin::init()
{
    if (m_actionBuildModel)
    {
        connect(m_actionBuildModel, &QAction::triggered, this, &SimulationPlugin::addModelSlot);
        IPluginView::getInstance().registerAction(QStringLiteral("视图"), QStringLiteral("仿真"), m_actionBuildModel);
    }
    if (m_actionRemoveModel)
    {
        connect(m_actionRemoveModel, &QAction::triggered, this, &SimulationPlugin::removeModelSlot);
        IPluginView::getInstance().registerAction(QStringLiteral("视图"), QStringLiteral("仿真"), m_actionRemoveModel);
    }
    return true;
}

bool SimulationPlugin::clean()
{
    return true;
}

void SimulationPlugin::addModelSlot()
{
    // 获取六自由度信息
}

void SimulationPlugin::removeModelSlot()
{
}

void SimulationPlugin::simulationSlot()
{
}
