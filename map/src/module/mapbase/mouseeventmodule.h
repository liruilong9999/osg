﻿#ifndef MOUSEEVENTMODULE_H
#define MOUSEEVENTMODULE_H
#include <vector>
#include <osgEarth/ImageLayer>

#include <common/TSingleton.hpp>
#include <osgEarth/GeoTransform>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/GeoData>
#include <functional>
#include <vector>
#include <memory>

#include "mapbase_global.h"

class MAPBASE_EXPORT MouseEventModule : public TSingleton<MouseEventModule>,
                                                 public osgGA::GUIEventHandler
{
    friend class TSingleton<MouseEventModule>;

public:
    using MouseMoveCallback = std::function<void(double lon, double lat, double elevation, double scale, double focalLength)>;

    // 设置地图节点
    void setMapNode(osgEarth::MapNode * mapNode);

    // 注册鼠标移动事件回调
    void registerMouseMoveCallback(MouseMoveCallback callback);
    // 处理鼠标事件
    bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & aa) override;

    double getFocalLength(osgViewer::Viewer * viewer, osgEarth::MapNode * mapNode);
    double getScale(osgViewer::Viewer * viewer);

    double getElevation(osg::ref_ptr<osgEarth::MapNode> mapNode, const osg::Vec3d & worldPos);

private:
    MouseEventModule();
    // 通知所有注册的回调函数
    void MouseEventModule::notifyMouseMoveCallbacks(double lon, double lat, double elevation, double scale, double focalLength);

    osgEarth::MapNode *            m_mapNode{nullptr};   // 地图节点，用于转换坐标
    std::vector<MouseMoveCallback> m_mouseMoveCallbacks; // 鼠标移动事件回调列表
    std::mutex                     m_mutex;              // 互斥锁保护回调列表
};

#endif