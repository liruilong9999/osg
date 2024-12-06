#ifndef LELEVATIONLAYER_H
#define LELEVATIONLAYER_H

#include <osgEarth/GDAL>
#include <osgEarth/Common>
#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>
#include <osgEarth/URI>

namespace osgEarth {

class LElevationLayer : public osgEarth::GDALElevationLayer
{
public:
    META_Layer(osgEarth, LElevationLayer, Options, GDALElevationLayer, MyElevation);
    //! Called by the constructor
    virtual void init();
    //! Establishes a connection to the repository
    virtual osgEarth::Status openImplementation();
    //! Closes down any GDAL connections
    virtual osgEarth::Status closeImplementation();
    //! Gets a heightfield for the given tile key
    virtual osgEarth::GeoHeightField createHeightFieldImplementation(const osgEarth::TileKey &    key,
                                                                     osgEarth::ProgressCallback * progress) const;

    void setScale(float scale);

protected:
    float _scale = 1; // 高程放大系数
};
}; // namespace osgEarth
#endif
