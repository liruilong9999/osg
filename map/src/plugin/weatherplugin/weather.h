#ifndef WEATHER_H
#define WEATHER_H
#include <vector>
#include <osgEarth/ImageLayer>

#include <singleton/TSingleton.hpp>
#include <osgEarth/GeoTransform>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/GeoData>
#include <functional>
#include <vector>
#include <memory>

#include <osgEarthDrivers\sky_simple\SimpleSkyNode>    //for the sky
#include <osgEarthDrivers\sky_simple\SimpleSkyOptions> //for the sky

class Weather : public osgGA::GUIEventHandler
{
public:
    Weather();
    // 添加日月星辰
    // osg::Node * addStars();
    osgEarth::Extension * addStars();
};

#endif
