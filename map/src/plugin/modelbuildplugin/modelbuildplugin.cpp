#include <QDebug>
#include <iappskeleton/iappview.h>
#include <lbase/lbase.h>
#include <QAction>

#include "modelbuildplugin.h"
#include "modelbuild.h"

DetectShowPlugin::DetectShowPlugin(QObject * parent)
    : QObject(parent)
{
    m_actionBuildModel  = new QAction(QStringLiteral("生成模型"), this);
    m_actionRemoveModel = new QAction(QStringLiteral("移除模型"), this);
    m_modelCtrl         = new ModelBuild;
}

QString DetectShowPlugin::getname()
{
    return QStringLiteral("模型生成插件");
}

bool DetectShowPlugin::init()
{
    IAppView * baseObj = dynamic_cast<IAppView *>(ObjectRegistry::instance().getObject("IPluginView"));
    if (baseObj)
    {
        if (m_actionBuildModel)
        {
            connect(m_actionBuildModel, &QAction::triggered, this, &DetectShowPlugin::addModelSlot);
            baseObj->registerAction(QStringLiteral("视图"), QStringLiteral("模型"), m_actionBuildModel);
        }
        if (m_actionRemoveModel)
        {
            connect(m_actionRemoveModel, &QAction::triggered, this, &DetectShowPlugin::removeModelSlot);
            baseObj->registerAction(QStringLiteral("视图"), QStringLiteral("模型"), m_actionRemoveModel);
        }
    }
    return true;
}

bool DetectShowPlugin::clean()
{
    return true;
}

void DetectShowPlugin::addModelSlot()
{
    if (m_modelCtrl)
        m_modelCtrl->addModel();
}

void DetectShowPlugin::removeModelSlot()
{
    if (m_modelCtrl)
        m_modelCtrl->removeModel();
}
