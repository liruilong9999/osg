#include <QDebug>
#include <iappskeleton/iappview.h>
#include <lbase/lbase.h>
#include <QAction>

#include "detectshow.h"
#include "detectshowplugin.h"

DetectShowPlugin::DetectShowPlugin(QObject * parent)
    : QObject(parent)
{
    m_actionAdd    = new QAction(QString("添加包络"), this);
    m_actionRemove = new QAction(QString("移除包络"), this);
}

QString DetectShowPlugin::getname()
{
    return QString("显示探测范围");
}

bool DetectShowPlugin::init()
{
    IAppView * baseObj = dynamic_cast<IAppView *>(ObjectRegistry::instance().getObject("IPluginView"));
    if (baseObj)
    {
        if (m_actionAdd)
        {
            connect(m_actionAdd, &QAction::triggered, this, &DetectShowPlugin::addSlot);
            baseObj->registerAction(QString("地图"), QString("显示"), m_actionAdd);
        }
        if (m_actionRemove)
        {
            connect(m_actionRemove, &QAction::triggered, this, &DetectShowPlugin::removeSlot);
            baseObj->registerAction(QString("地图"), QString("显示"), m_actionRemove);
        }
    }
    LEventBus::instance().subscribe("VIEW_INITIALIZED", SLOT(showDetect), this);
    return true;
}

bool DetectShowPlugin::clean()
{
    return true;
}

void DetectShowPlugin::addSlot()
{
    if (m_detectShow)
        m_detectShow->add();
}

void DetectShowPlugin::removeSlot()
{
    if (m_detectShow)
        m_detectShow->remove();
}

void DetectShowPlugin::showDetect(const QVariant & var)
{
    m_detectShow = new DetectShow;
}
