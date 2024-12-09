#ifndef FEATUREMODULE_H
#define FEATUREMODULE_H
#include <vector>
#include <osgEarth/ImageLayer>

#include <common/TSingleton.hpp>
#include <osgEarth/GeoTransform>
#include <osgEarth/PlaceNode>

#include "mapbase_global.h"

class MAPBASE_EXPORT FeatureModule : public TSingleton<FeatureModule>
{
    friend class TSingleton<FeatureModule>;

public:
    osg::ref_ptr<osg::Group> createRadar(double radius, osg::Vec4 envelopeColor, osg::Vec4 scanColor, double minBeamAngle, double maxBeamAngle, double duration, int segments = 100);
};

#endif
