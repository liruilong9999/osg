#include <osgDB/ReadFile>
#include <osgEarth/ShaderGenerator>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osg/MatrixTransform>

#include <module/nodemodule/nodemodule.h>

#include "modelmodule.h"

osg::ref_ptr<osg::Group> ModelModule::addModel(osg::Vec3d position, double scale, const std::string & modelPath)
{
    // 读取一个三维模型
    osg::Node * treeNode = osgDB::readNodeFile(modelPath);
    if (!treeNode)
    {
        std::cerr << "Error: Failed to load model from " << modelPath << std::endl;
        return nullptr;
    }

    osgEarth::ShaderGenerator shader; // 为这个三维模型添加自动Shader
    treeNode->accept(shader);

    // 构建缩放矩阵将三个维度缩小到指定倍数
    osg::MatrixTransform * scaleTransform = new osg::MatrixTransform;
    osg::Matrix            scaleMatrix    = osg::Matrix::scale(osg::Vec3(scale, scale, scale));
    scaleTransform->setMatrix(scaleMatrix);
    scaleTransform->addChild(treeNode);

    osgEarth::GeoTransform * geoTransform = new osgEarth::GeoTransform; // 构建一个地球坐标系位置节点
    geoTransform->setPosition(osgEarth::GeoPoint(osgEarth::SpatialReference::get("wgs84"), position));
    geoTransform->addChild(scaleTransform); // 将模型的父节点加入到地球坐标系位置节点中

    return geoTransform;
}
