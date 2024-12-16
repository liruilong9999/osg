#include <QDebug>

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>
#include <module/layermodule/layermodule.h>
#include <module/mapmodule/mapmodule.h>

#include "gridctrl.h"

void GridCtrl::showOrHideGrid()
{
    m_clicked                   = !m_clicked;
    osgEarth::MapNode * mapNode = NodeModule::getInstance()->getRootMapNode();
    if (mapNode && m_clicked)
    {
        if (!m_pGraticule)
            m_pGraticule = new osgEarth::Util::GeodeticGraticule();
        m_pGraticule->setEdgeLabelsVisible(true);
        m_pGraticule->setColor(osgEarth::Color(osg::Vec4f(1, 1, 1, 1)));
        m_pGraticule->addedToMap(mapNode->getMap());
        mapNode->getMap()->addLayer(m_pGraticule);
    }
    else
    {
        if (m_pGraticule)
        {
            mapNode->getMap()->removeLayer(m_pGraticule);
            m_pGraticule = nullptr;
        }
    }
}

// 显示或隐藏网格
// void GridCtrl::showOrHideGrid()
//{
//    m_clicked                   = !m_clicked; // 切换点击状态
//    osgEarth::MapNode * mapNode = NodeModule::getInstance()->getRootMapNode();
//    if (mapNode && m_clicked)
//    { // 如果存在地图节点且点击状态为true
//        if (!m_pGraticule)
//        {
//            m_pGraticule = new osgEarth::Util::GeodeticGraticule();
//        }
//        m_pGraticule->setEdgeLabelsVisible(true);                                 // 显示经纬度标签
//        m_pGraticule->setEdgeLabelColor(osgEarth::Color(osg::Vec4f(1, 1, 1, 1))); // 设置标签颜色为白色
//        m_pGraticule->setEdgeLabelFontSize(12);                                   // 设置标签字体大小为12
//        m_pGraticule->setColor(osgEarth::Color(osg::Vec4f(1, 1, 1, 1)));          // 设置网格颜色为白色
//        m_pGraticule->addedToMap(mapNode->getMap());                              // 将网格对象添加到地图
//        mapNode->getMap()->addLayer(m_pGraticule);                                // 将网格图层添加到地图中
//    }
//    else
//    {
//        if (m_pGraticule)
//        {                                                 // 如果网格对象存在且点击状态为false
//            mapNode->getMap()->removeLayer(m_pGraticule); // 从地图中移除网格图层
//            m_pGraticule = nullptr;                       // 删除网格对象
//        }
//    }
//}
