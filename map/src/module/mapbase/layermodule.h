#ifndef LAYERMODULE_H_20240805
#define LAYERMODULE_H_20240805

#include <common/TSingleton.hpp>
#include <osgEarth/Geometry>
#include <osgEarth/Color>

#include "mapbase_global.h"

class MAPBASE_EXPORT LayerModule : public TSingleton<LayerModule>
{
    friend class TSingleton<LayerModule>;

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	添加一个多边形（这个多边形是贴地的，有需求再完善这个接口）. </summary>
    ///
    /// <remarks>	Liruilong, 2024/8/5. </remarks>
    ///
    /// <param name="posVec">	多边形的点集合. </param>
    /// <param name="hight"> 	多边形高度，如果小于等于0为多边形,贴地，如果大于0为多边柱，不贴地（如果地图未显示就是在地底了）. </param>
    /// <param name="color"> 	多边形颜色. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    osg::ref_ptr<osg::Node> addPolygon(osgEarth::Vec3dVector posVec, double hight = 0, osgEarth::Color color = osgEarth::Color(1, 0.5, 0.2, 1));

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	在指定坐标添加文本. </summary>
    ///
    /// <remarks>	Liruilong, 2024/8/5. </remarks>
    ///
    /// <param name="lon">  	The lon. </param>
    /// <param name="lat">  	The lat. </param>
    /// <param name="text"> 	The text. </param>
    /// <param name="color">	The color. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    osg::ref_ptr<osg::Node> addText(double lon, double lat, std::string text, std::string color);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	在指定坐标添加文本（增加高度设置）. </summary>
    ///
    /// <remarks>	Liruilong, 2024/8/5. </remarks>
    ///
    /// <param name="lon">  	The lon. </param>
    /// <param name="lat">  	The lat. </param>
    /// <param name="alt">  	The alternate. </param>
    /// <param name="text"> 	The text. </param>
    /// <param name="color">	The color. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    osg::ref_ptr<osg::Node> addText(double lon, double lat, double alt, std::string text, std::string color);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	指定地点添加地点图标. </summary>
    ///
    /// <remarks>	Liruilong, 2024/8/5. </remarks>
    ///
    /// <param name="lon">	The lon. </param>
    /// <param name="lat">	The lat. </param>
    /// <param name="alt">	(Optional) The alternate. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    osg::ref_ptr<osg::Node> addPlaceNode(std::string text, double lon, double lat, double alt /*= 0*/);
    osg::ref_ptr<osg::Node> addImage(const osg::Vec2d lowerLeft, const osg::Vec2d lowerRight, const osg::Vec2d upperLeft, const osg::Vec2d upperRight, const std::string path = "./data/fractal.png");

private:
};

#endif
