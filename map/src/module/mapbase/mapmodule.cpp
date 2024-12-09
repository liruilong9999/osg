
#include <osgEarth/Notify>
#include <osgEarth/EarthManipulator>
#include <osgEarth/MapNode>
#include <osgEarth/Threading>
#include <osgEarth/ShaderGenerator>
#include <osgEarth/Controls>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgUtil/Optimizer>
#include <iostream>

#include <osgEarth/Common>
#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>
#include <osgEarth/URI>

#include <osgEarth/MBTiles>
#include <osgEarth/Metrics>
#include <osgEarth/GDAL>
#include <osgEarth/TMS>
#include <osgEarth/XYZ>
#include <osgEarth/WMS>
#include <osgEarth/Composite>
#include <osgEarth/Profile>

#include <osgEarthDrivers\sky_simple\SimpleSkyNode>    //for the sky
#include <osgEarthDrivers\sky_simple\SimpleSkyOptions> //for the sky

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>

#include "mapmodule.h"
#include "lelevationlayer.h"

osgEarth::LElevationLayer *              g_elevationLayer = nullptr;
osgEarth::Util::Controls::LabelControl * g_labelHeight    = nullptr;
osgEarth::MapNode *                      g_mapNode        = nullptr;

struct MyControlHandler : public osgEarth::Util::Controls::ControlEventHandler
{
    virtual void onValueChanged(osgEarth::Util::Controls::Control * control, float value)
    {
        char buff[64];
        sprintf(buff, "heightScale:%5.2f", value);
        g_labelHeight->setText(std::string(buff));
        g_elevationLayer->setScale(value); // 更新高程放大系数
        // g_elevationLayer->dirty();                            // 对于已绘制瓦片无效
        g_mapNode->getTerrain()->notifyMapElevationChanged(); // 对于已绘制瓦片无效too
    }
};
// 生成GUI
osgEarth::Util::Controls::ControlCanvas * makeGUI()
{
    // Event handler构建一个共享的Handler对象，当然不同Control可以设置单独的Handler
    osg::ref_ptr<MyControlHandler> controlHandler = new MyControlHandler;
    // UI Canvase
    osgEarth::Util::Controls::ControlCanvas * canvas = new osgEarth::Util::Controls::ControlCanvas();
    // container
    osgEarth::Util::Controls::VBox * vbox = new osgEarth::Util::Controls::VBox(
        osgEarth::Util::Controls::Container::Alignment::ALIGN_LEFT,
        osgEarth::Util::Controls::Container::Alignment::ALIGN_TOP,
        osgEarth::Util::Controls::Gutter(2, 2, 2, 2),
        5 // the margin between controls inside.
    );
    vbox->setBackColor(0.8, 0.8, 0.8, 0.5);
    // label for heightScale
    osgEarth::Util::Controls::LabelControl * labelHeight = new osgEarth::Util::Controls::LabelControl("heightScale:1");
    vbox->addControl(labelHeight);
    g_labelHeight = labelHeight;
    // slider for height scale
    osgEarth::Util::Controls::HSliderControl * sliderHeight = new osgEarth::Util::Controls::HSliderControl(
        1,  // min
        30, // max
        1,  // init
        controlHandler.get());
    sliderHeight->setUserValue("ID", 1);
    sliderHeight->setWidth(200);
    sliderHeight->setHeight(20);
    vbox->addControl(sliderHeight);
    canvas->addControl(vbox);
    return canvas;
}

void MapModule::init()
{
    addConfigData();
}

void MapModule::addConfigData()
{
    // 这里先不读，直接写死路径  TODO
    std::string str2  = "./data/env/world.tif";
    MapDataType type2 = MapDataType::Type_Tiff;
    LayerInfo   layer2;
    layer2.layerUrl  = str2;
    layer2.layerType = type2;
    m_layerVec.push_back(layer2);
    //std::string str1 = "./data/env/img/{z}/{x}/{y}.png";
    //// str1  = "D:/code/git/osgEarth/bin/env/img/{z}/{x}/{y}.png";
    //MapDataType type1 = MapDataType::Type_XYZ;
    //LayerInfo   layer;
    //layer.layerUrl  = str1;
    //layer.layerType = type1;
    //m_layerVec.push_back(layer);
    for (auto & layerInfo : m_layerVec)
    {
        switch (layerInfo.layerType)
        {
        case MapDataType::Type_Tiff :
            addGeoTiff(layerInfo);
            break;
        case MapDataType::Type_XYZ :
            addXYZ(layerInfo);
            break;
        default :
            break;
        }
    }
}

void MapModule::addGeoTiff(LayerInfo & layerInfo)
{
    osg::ref_ptr<osgEarth::GDALImageLayer> gdalLayer = new osgEarth::GDALImageLayer();
    gdalLayer->setURL(osgEarth::URI(layerInfo.layerUrl));
    layerInfo.imageLayer = gdalLayer;
}

void MapModule::addMBTiles(LayerInfo & layerInfo)
{
    osg::ref_ptr<osgEarth::MBTilesImageLayer> mbtLayer = new osgEarth::MBTilesImageLayer();
    mbtLayer->setURL(osgEarth::URI(layerInfo.layerUrl));
    layerInfo.imageLayer = mbtLayer;
}

void MapModule::addTMS(LayerInfo & layerInfo)
{
    osg::ref_ptr<osgEarth::TMSImageLayer> someLayer = new osgEarth::TMSImageLayer();
    someLayer->setURL(osgEarth::URI(layerInfo.layerUrl));
    layerInfo.imageLayer = someLayer;
}

void MapModule::addWMS(LayerInfo & layerInfo)
{
    osg::ref_ptr<osgEarth::WMSImageLayer> someLayer = new osgEarth::WMSImageLayer;
    someLayer->setURL(osgEarth::URI(layerInfo.layerUrl));
    someLayer->setFormat("png");
    someLayer->setStyle("default");
    someLayer->setLayers("country_bounds");
    layerInfo.imageLayer = someLayer;
}

void MapModule::addXYZ(LayerInfo & layerInfo)
{
    osg::ref_ptr<osgEarth::XYZImageLayer> someLayer = new osgEarth::XYZImageLayer;
    someLayer->setURL(osgEarth::URI(layerInfo.layerUrl));
    someLayer->setProfile(osgEarth::Profile::create(osgEarth::Profile::SPHERICAL_MERCATOR));
    layerInfo.imageLayer = someLayer;
}

void MapModule::addContour(LayerInfo & layerInfo)
{
}

osg::Node * MapModule::addHeight()
{
    // osgEarth::Map *     map    = NodeModule::getInstance()->getRootMapNode()->getMap();
    osg::ref_ptr<osgEarth::MapNode> mapNode = NodeModule::getInstance()->getRootMapNode();
    osgViewer::Viewer *             viewer  = ViewerModule::getInstance()->getOsgViewer();
    if (!mapNode || !viewer)
        return nullptr;
    osgEarth::LElevationLayer * myElevation = new osgEarth::LElevationLayer;
    myElevation->setURL(osgEarth::URI("./data/env/dem_cog_0.0833f.tif"));
    myElevation->setDataVariance(osg::Object::DataVariance::DYNAMIC); // this is not working for update height.
    mapNode->getMap()->addLayer(myElevation);
    g_elevationLayer = myElevation;
    //// 天空效果
    //{
    //    // SkyOptions options;
    //    osgEarth::SimpleSky::SimpleSkyOptions options;
    //    // options.quality()             = osgEarth::SkyOptions::QUALITY_DEFAULT;
    //    options.ambient()             = 0.001; // 控制环境光强度
    //    options.exposure()            = 10.f;  // 控制白天的亮度
    //    options.atmosphereVisible()   = true;  // 大气层厚度是否可见
    //    options.atmosphericLighting() = true;  // 大气散射光是否可见
    //    options.sunVisible()          = true;
    //    options.moonVisible()         = true;
    //    options.starsVisible()        = true;
    //    options.usePBR()              = true;
    //    options.hours()               = 20;
    //    // 添加天空模型
    //    mapNode->addExtension(osgEarth::Extension::create("sky_simple", options)); // 这里不能使用addChild, Extension是一种更复杂的对象
    //    // set black background color
    //    viewer->getCamera()->setClearColor(osg::Vec4(0, 0, 0, 1)); // 设置宇宙背景颜色为黑色
    //}
    // controls
    // mapNode->addChild(makeGUI());
    g_mapNode = mapNode;
    return makeGUI();
    // viewer->setSceneData(mapNode);
}

std::vector<LayerInfo> & MapModule::getLayerVec()
{
    return m_layerVec;
}

MapModule::MapModule()
{
    init();
}
