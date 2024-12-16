#ifndef Scutcheon_H
#define Scutcheon_H
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

#include <osgEarthDrivers\sky_simple\SimpleSkyNode>    //for the sky
#include <osgEarthDrivers\sky_simple\SimpleSkyOptions> //for the sky

class Scutcheon : public osgGA::GUIEventHandler
{
public:
    Scutcheon();

    osg::ref_ptr<osg::Node> createScucheon();
};

#endif
