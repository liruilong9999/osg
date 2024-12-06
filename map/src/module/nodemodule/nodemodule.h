#ifndef NODEMODULE_H
#define NODEMUDELE_H
#include <QSharedPointer>
#include <osgEarth/ImageLayer>

#include <common/TSingleton.hpp>
#include "nodemodule_global.h"

struct NodeModulePrivate;
class NODEMODULE_EXPORT NodeModule : public TSingleton<NodeModule>
{
    friend class TSingleton<NodeModule>;

public:
    void addChildNode(osg::ref_ptr<osg::Node> childNode);
    void addLayer(osg::ref_ptr<osgEarth::ImageLayer> layer);

    osg::ref_ptr<osg::Group> &        getRootNode();
    osg::ref_ptr<osgEarth::MapNode> & getRootMapNode();
    void                              setRootMapNode(osg::ref_ptr<osgEarth::MapNode>);

private:
    NodeModule();
    QSharedPointer<NodeModulePrivate> m_p;
};

#endif
