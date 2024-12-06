#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

#include <osgEarth/Sky>

#include <osgEarth/ShaderGenerator>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osgEarth/ElevationQuery>

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>

#include "weather.h"

Weather::Weather()
{
}

// osg::Node * Weather::addStars()
//{
//     // 创建 osgEarth Viewer
//     osg::ref_ptr<osgEarth::MapNode> mapNode = NodeModule::getInstance()->getRootMapNode();
//     osg::ref_ptr<osgViewer::Viewer> viewer  = ViewerModule::getInstance()->getOsgViewer();

//    if (mapNode.valid())
//    {
//        // viewer->setSceneData(mapNode);

//        // 创建 SkyNode
//        osg::ref_ptr<osgEarth::Util::SkyNode> skyNode = osgEarth::Util::SkyNode::create();
//        skyNode->setDateTime(osgEarth::DateTime(2024, 8, 12, 12.0)); // 设置日期时间
//        skyNode->attach(viewer, 0);                                  // 附加到 viewer 上
//        skyNode->setLighting(true);                                  // 启用光照效果
//        skyNode->setAtmosphereVisible(true);                         // 启用大气效果
//        return skyNode;
//    }
//    return nullptr;
//}

osgEarth::Extension * Weather::addStars()
{
    // SkyOptions options;
    osgEarth::SimpleSky::SimpleSkyOptions options;
    // options.quality()             = osgEarth::SkyOptions::QUALITY_DEFAULT;

    options.ambient() = 0.201; // 控制环境光强度
    // options.exposure()            = 6.f;   // 控制白天的亮度
    // options.atmosphereVisible()   = false; // 大气层厚度是否可见
    // options.atmosphericLighting() = true; // 大气散射光是否可见
    options.sunVisible()   = true;
    options.moonVisible()  = true;
    options.starsVisible() = true;
    options.usePBR()       = true;
    options.moonImageURI() = "./data/moon_1024x512.jpg";
    // options.usePBR() = false;
    //  options.hours()               = 1;
    return osgEarth::Extension::create("sky_simple", options);
}
