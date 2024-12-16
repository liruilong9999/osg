
#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>
#include <module/layermodule/layermodule.h>
#include <module/mapmodule/mapmodule.h>
#include <module/featuremodule/featuremodule.h>
#include <module/modelmodule/modelmodule.h>
#include <lbase/lbase.h>

#include <osgDB/ReadFile>

#include <osgEarth/Style>
#include <osgEarth/TextSymbol>
#include <osgEarth/PlaceNode>

#include "detectshow.h"

void DetectShow::add()
{
    // 雷达参数
    double    radarRadius = 10000.0;
    osg::Vec4 envelopeColor(1.0, 0.0, 0.0, 0.5); // 红色，半透明
    osg::Vec4 scanColor(1.0, 0.0, 0.0, 0.3);     // 红色，半透明
    double    startAngle = 0.0;                  // 扫描扇区起始角度（度）
    double    sweepAngle = 90.0;                 // 扫描扇区扫掠角度（度）
    double    duration   = 3;                    // 扫描周期，单位：秒

    // 创建雷达节点
    osg::ref_ptr<osg::Group> radarNode = FeatureModule::getInstance()->createRadar(radarRadius, envelopeColor, scanColor, startAngle, sweepAngle, duration);

    // 指定雷达中心的经度和纬度
    double radarLongitude = 120.0; // 经度
    double radarLatitude  = 30.0;  // 纬度

    // 创建GeoTransform以放置雷达几何节点在指定的地理位置
    osg::ref_ptr<osgEarth::GeoTransform> geoTransform = new osgEarth::GeoTransform();
    geoTransform->setPosition(osgEarth::GeoPoint(NodeModule::getInstance()->getRootMapNode()->getMapSRS(), radarLongitude, radarLatitude));
    geoTransform->addChild(radarNode.get());

    // 将GeoTransform添加到场景根节点
    NodeModule::getInstance()->getRootNode()->addChild(geoTransform.get());

    m_radarList.push_back(geoTransform);

    osg::Vec3d pos2(120, 30, 0);
    LayerModule::getInstance()->addText(120, 30, 0, QString::fromLocal8Bit("雷达").toStdString(), "#5f5f5f");

    osg::ref_ptr<osg::Node> modelNode = ModelModule::getInstance()->addModel(pos2, 1, "cow.osg");

    NodeModule::getInstance()->getRootNode()->addChild(modelNode.get());
    m_modelList.push_back(modelNode);

    osg::ref_ptr<osg::Node> textNode = LayerModule::getInstance()->addText(120, 30, 0, QString("雷达1").toStdString(), "FFFFFF");

    NodeModule::getInstance()->getRootNode()->addChild(textNode.get());
    m_textList.push_back(textNode);
}

void DetectShow::remove()
{
    for (auto geoTransform : m_radarList)
        NodeModule::getInstance()->getRootNode()->removeChild(geoTransform.get());
    for (auto geoTransform : m_modelList)
        NodeModule::getInstance()->getRootNode()->removeChild(geoTransform.get());
    for (auto geoTransform : m_textList)
        NodeModule::getInstance()->getRootNode()->removeChild(geoTransform.get());
}
