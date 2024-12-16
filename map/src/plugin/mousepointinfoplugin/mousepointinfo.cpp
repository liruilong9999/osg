#include <osgDB/ReadFile>
#include <osgEarth/ShaderGenerator>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osg/MatrixTransform>

#include <osgEarth/ElevationQuery>

#include <module/nodemodule/nodemodule.h>

#include "mousepointinfo.h"

MousePointInfo::MousePointInfo()
{
}

void MousePointInfo::setMapNode(osgEarth::MapNode * mapNode)
{
    m_mapNode = mapNode;
}

void MousePointInfo::registerMouseMoveCallback(MousePointInfo::MouseMoveCallback callback)
{
    m_mouseMoveCallbacks.push_back(callback);
}

void MousePointInfo::notifyMouseMoveCallbacks(double lon, double lat, double elevation, double scale, double focalLength)
{
    // 通知所有注册的回调函数
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto & callback : m_mouseMoveCallbacks)
    {
        callback(lon, lat, elevation, scale, focalLength);
    }
}

// 处理鼠标事件，获取鼠标位置的经纬度信息并通知回调函数
bool MousePointInfo::handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa)
{
    if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
    {
        double x = double(ea.getX());
        double y = double(ea.getY());

        osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer *>(&aa);
        if (!viewer || !m_mapNode)
            return false;

        osg::Vec3d          world;
        osgEarth::Terrain * terrain = m_mapNode->getTerrain();
        if (terrain && terrain->getWorldCoordsUnderMouse(viewer, x, y, world))
        {
            osgEarth::GeoPoint mapPoint;
            if (!mapPoint.fromWorld(m_mapNode->getMapSRS(), world))
            {
                return false;
            }
            double lon      = mapPoint.x();
            double lat      = mapPoint.y();
            double diatance = getFocalLength(viewer, m_mapNode) / 1000.0;
            double scale    = getScale(viewer);

            // 使用第一个重载
            // bool success = terrain->getHeight(m_mapNode->getMapSRS(), world.x(), world.y(), &heightAboveMSL, &heightAboveEllipsoid);

            double elevation = getElevation(m_mapNode, world);
            elevation        = elevation < 1 ? 0.0 : elevation;
            // 通知所有注册的回调函数
            notifyMouseMoveCallbacks(lon, lat, elevation, scale, diatance);
        }
        return true;
    }
    return false;
}

// 计算视点焦距
double MousePointInfo::getFocalLength(osgViewer::Viewer * viewer, osgEarth::MapNode * mapNode)
{
    // 获取相机位置
    osg::Camera * camera = viewer->getCamera();
    if (!camera)
        return 0;
    osg::Matrixd viewMatrix     = camera->getViewMatrix();
    osg::Vec3d   cameraPosition = osg::Vec3d(viewMatrix(3, 0), viewMatrix(3, 1), viewMatrix(3, 2));

    // 地球表面高度通常需要地形数据或地球模型

    osgEarth::GeoPoint cameraGeoPoint;
    cameraGeoPoint.fromWorld(mapNode->getMapSRS(), cameraPosition);

    // 获取地球表面高度
    double surfaceHeight = 6378137.0; // 你可能需要通过地形数据来计算准确的表面高度
    // 计算相机到地球表面的距离
    double distance = cameraPosition.length() - surfaceHeight;

    return distance;
}

double MousePointInfo::getElevation(osg::ref_ptr<osgEarth::MapNode> mapNode, const osg::Vec3d & worldPos)
{
    // 转换到地球坐标系
    osgEarth::GeoPoint geoPoint;
    geoPoint.fromWorld(mapNode->getMapSRS(), worldPos);

    // 获取高程
    double                   query_resolution = 0.00000001;
    double                   out_hamsl        = 0.0;
    osgEarth::ElevationQuery query(mapNode->getMap());
    return query.getElevation(osgEarth::GeoPoint(mapNode->getMapSRS(), geoPoint.x(), geoPoint.y(), 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
                              out_hamsl,
                              &query_resolution);
}

// 计算比例尺
double MousePointInfo::getScale(osgViewer::Viewer * viewer)
{
    if (!viewer)
        return 1.0;
    osg::Camera * camera = viewer->getCamera();
    if (!camera)
        return 1.0;
    // 计算比例尺（简单估计）
    double fovy, aspectRatio, zNear, zFar;
    camera->getProjectionMatrixAsPerspective(fovy, aspectRatio, zNear, zFar);

    //    osg::Matrixd projectionMatrix = camera->getProjectionMatrix();
    //    double       scale            = 1.0 / projectionMatrix(1, 1); // 取决于投影矩阵的第一个缩放因子
    return zNear;
}
