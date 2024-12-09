#ifndef MODELMODULE_H
#define MODELMODULE_H
#include <vector>
#include <osgEarth/ImageLayer>

#include <common/TSingleton.hpp>
#include <osgEarth/GeoTransform>

#include "mapbase_global.h"

class MAPBASE_EXPORT ModelModule : public TSingleton<ModelModule>
{
    friend class TSingleton<ModelModule>;

public:
    // 添加模型
    osg::ref_ptr<osg::Group> addModel(osg::Vec3d position, double scale, const std::string & modelPath);

protected:
    ~ModelModule() = default;
    ModelModule()  = default;

private:
    ModelModule(const ModelModule &)             = delete;
    ModelModule & operator=(const ModelModule &) = delete;

    osg::ref_ptr<osgEarth::MapNode> m_rootMapNode{nullptr};
};

#endif
