
#include <osgEarth/MapNode>
#include <osgEarth/Terrain>
#include <osgViewer/Viewer>
#include <osgEarth/GeoData>
#include <osgEarth/ElevationQuery>
#include <osgEarth/EarthManipulator>

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>
#include <module/layermodule/layermodule.h>
#include <module/mapmodule/mapmodule.h>

#include <lib/leventbus/leventbus.h>

#include "earthwidget.h"

EarthWidget::EarthWidget(QWidget * parent)
    : osgQOpenGLWidget(parent)
{
    this->setMouseTracking(true);
    connect(this, &osgQOpenGLWidget::initialized, this, &EarthWidget::initializedSlots);
}

EarthWidget::~EarthWidget()
{
}

void EarthWidget::initializedSlots()
{
    // 创建地图元素
    osg::ref_ptr<osgEarth::Map> rootMap = new osgEarth::Map;
    // 设置场景viewer
    ViewerModule::getInstance()->setOsgViewer(this->getOsgViewer());

    osgViewer::Viewer * viewer = ViewerModule::getInstance()->getOsgViewer();

    viewer->setReleaseContextAtEndOfFrameHint(false);

    osgEarth::EarthManipulator * em = new osgEarth::Util::EarthManipulator;
    viewer->setCameraManipulator(em);

    for (LayerInfo layerInfo : MapModule::getInstance()->getLayerVec())
    {
        rootMap->addLayer(layerInfo.imageLayer);
    }

    // 设置地图元素到mapNode根节点
    osg::ref_ptr<osgEarth::MapNode> rootMapNode = new osgEarth::MapNode(rootMap.get());
    NodeModule::getInstance()->setRootMapNode(rootMapNode); // Assuming you have a setter
    // 将节点管理器的osg节点作为地图根节点的下一级节点
    rootMapNode->addChild(NodeModule::getInstance()->getRootNode());
    // 将地图根节点加入到osg场景中
    viewer->setSceneData(rootMapNode);
    viewer->getCamera()->setClearColor(osg::Vec4(0, 0, 0, 1));

    // 设置地图投影
    osgEarth::SpatialReference * srs = osgEarth::SpatialReference::get("epsg:4326");
    rootMap->setProfile(osgEarth::Profile::create(srs));

    // 设置相机参数
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    camera->setProjectionMatrixAsPerspective(
        30.0,                                                                                  // 视场角
        static_cast<double>(camera->getViewport()->width()) / camera->getViewport()->height(), // 宽高比
        0.1,                                                                                   // 近裁剪平面
        10000.0                                                                                // 远裁剪平面
    );

    // 将相机位置设置为一个合理的默认值
    em->setHomePosition(osg::Vec3d(-100.0, 0.0, 100.0), osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, 0.0, 1.0));
    em->home(0.0);
    // 设置默认位置和视角

    osgEarth::Viewpoint vp = em->getViewpoint();

    vp.setFocalPoint(osgEarth::GeoPoint(NodeModule::getInstance()->getRootMapNode()->getMap()->getSRS(), 110, 25, 100000));
    em->setViewpoint(vp); // 设置初始视角和朝向

    LEventBus::getInstance()->publish("VIEW_INITIALIZED", QVariant::fromValue(this));
}
