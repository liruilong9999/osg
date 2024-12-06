#include <osg/Group>
#include <osgEarth/MapNode>
#include <osgEarth/EarthManipulator>

#include "nodemodule.h"

struct NodeModulePrivate
{
    // 构造函数，用于初始化节点管理器
    NodeModulePrivate()
    {
        rootNode = new osg::Group;
        mapNode  = new osgEarth::MapNode;
    }
    osg::ref_ptr<osg::Group>        rootNode{nullptr}; // osg场景根节点
    osg::ref_ptr<osgEarth::MapNode> mapNode{nullptr};  // osgearth地图根节点
};

void NodeModule::addChildNode(osg::ref_ptr<osg::Node> childNode)
{
}

void NodeModule::addLayer(osg::ref_ptr<osgEarth::ImageLayer> layer)
{
    // m_p->rootMap->addLa
}

osg::ref_ptr<osg::Group> & NodeModule::getRootNode()
{
    return m_p->rootNode;
}

osg::ref_ptr<osgEarth::MapNode> & NodeModule::getRootMapNode()
{
    return m_p->mapNode;
}

void NodeModule::setRootMapNode(osg::ref_ptr<osgEarth::MapNode> node)
{
    m_p->mapNode = node;
}

NodeModule::NodeModule()
{
    m_p.reset(new NodeModulePrivate);
}
