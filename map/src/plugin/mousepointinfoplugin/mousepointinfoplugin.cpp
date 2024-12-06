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

#include "mousepointinfoplugin.h"
#include "mousepointinfo.h"

QLabel * label{nullptr}; // 鼠标点信息label

// 鼠标事件回调函数
void handleMouseMove(double lon, double lat, double elevation, double scale, double focalLength)
{
    if (!label)
        return;
    QString pointStr = QString(QStringLiteral("经度:%1° 纬度:%2° 高度:%3m 视点焦距:%4km 比例尺:1:%5 "))
                           .arg(QString::number(lon, 'f', 4))
                           .arg(QString::number(lat, 'f', 4))
                           .arg(QString::number(elevation, 'f', 2))
                           .arg(QString::number(focalLength, 'f', 4))
                           .arg(QString::number(scale, 'f', 4));
    label->setText(pointStr);
}

MousePointInfoPlugin::MousePointInfoPlugin(QObject * parent)
    : QObject(parent)
{
}

QString MousePointInfoPlugin::getname()
{
    return QStringLiteral("模型生成插件");
}

bool MousePointInfoPlugin::init()
{
    m_mousePointInfo = new MousePointInfo;

    LEventBus::getInstance()->subscribe("VIEW_INITIALIZED", [this](const QVariant & data) {
        osgViewer::Viewer * viewer = ViewerModule::getInstance()->getOsgViewer();
        if (viewer)
        {
            // 创建一个简单的地图节点
            osg::ref_ptr<osgEarth::MapNode> mapNode = NodeModule::getInstance()->getRootMapNode();
            osgViewer::Viewer *             viewer  = ViewerModule::getInstance()->getOsgViewer();
            if (!mapNode || !viewer)
                return false;

            // 设置地图节点并添加鼠标事件处理器
            m_mousePointInfo->setMapNode(mapNode);
            viewer->addEventHandler(m_mousePointInfo);

            label = new QLabel(IPluginView::getInstance().getMainWindow());
            IPluginView::getInstance().getMainWindow()->statusBar()->addWidget(label);

            // 注册鼠标移动事件的回调函数
            m_mousePointInfo->registerMouseMoveCallback(handleMouseMove);
        }
    });

    return true;
}

bool MousePointInfoPlugin::clean()
{
    return true;
}
