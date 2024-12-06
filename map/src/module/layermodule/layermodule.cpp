

#include <osgEarth/AnnotationLayer>
#include <osgEarth/Geometry>
#include <osgEarth/Style>
#include <osgEarth/AltitudeSymbol>
#include <osgEarth/FeatureNode>
#include <osgEarth/LabelNode>
#include <osgEarth/PlaceNode>
#include <osgEarth/ImageOverlay>
#include <osgDB/ReadFile>

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>

#include "layermodule.h"

osg::ref_ptr<osg::Node> LayerModule::addPolygon(osgEarth::Vec3dVector posVec, double hight, osgEarth::Color color)
{
    // 创建一个 Polygon（多边形）几何对象
    osgEarth::Geometry * tempGeom = new osgEarth::Polygon;

    // 将位置向量 posVec 中的每个点添加到多边形几何对象中
    for (auto pos : posVec)
    {
        tempGeom->push_back(pos);
    }

    // 闭合多边形
    tempGeom->close();

    // 创建样式对象，用于设置多边形的外观
    osgEarth::Style featureNodeStyle;

    // 获取或创建多边形符号（PolygonSymbol），并设置填充颜色
    osgEarth::PolygonSymbol * polygonSymbol = featureNodeStyle.getOrCreateSymbol<osgEarth::PolygonSymbol>();
    polygonSymbol->fill()->color()          = color; // 设置填充颜色
    polygonSymbol->outline()                = true;  // 启用轮廓线

    // 获取或创建线符号（LineSymbol），用于设置轮廓线的外观
    osgEarth::LineSymbol * lineSym = featureNodeStyle.getOrCreate<osgEarth::LineSymbol>();
    lineSym->stroke()->color()     = osgEarth::Color::Yellow; // 设置轮廓线颜色为黄色
    lineSym->stroke()->width()     = 3.f;                     // 设置轮廓线宽度为3

    // 获取或创建海拔符号（AltitudeSymbol），用于设置多边形的高度模式
    osgEarth::AltitudeSymbol * altiSymbol = featureNodeStyle.getOrCreateSymbol<osgEarth::AltitudeSymbol>();
    altiSymbol->clamping()                = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN; // 设置多边形贴地
    altiSymbol->technique()               = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;  // 设置多边形的技术为铺展

    if (hight > 0)
    {
        // 获取或创建拉伸符号（ExtrusionSymbol），用于设置多边形的高度
        osgEarth::ExtrusionSymbol * extrude = featureNodeStyle.getOrCreate<osgEarth::ExtrusionSymbol>();
        extrude->height()                   = hight; // 如果高度大于0，则设置多边形的高度
    }

    // 创建一个 FeatureNode 对象，表示多边形要素，并应用样式
    osgEarth::FeatureNode * featureNode = new osgEarth::FeatureNode(
        new osgEarth::Feature(tempGeom, osgEarth::SpatialReference::get("wgs84")), featureNodeStyle);
    return featureNode;
}

osg::ref_ptr<osg::Node> LayerModule::addText(double lon, double lat, std::string text, std::string color)
{
    return addText(lon, lat, 0.0, text, color);
}

osg::ref_ptr<osg::Node> LayerModule::addText(double lon, double lat, double alt, const std::string text, const std::string color)
{
    osg::ref_ptr<osgEarth::MapNode> mapNode = NodeModule::getInstance()->getRootMapNode();
    if (mapNode)
    {
        const osgEarth::SpatialReference * srs = mapNode->getMapSRS();
        if (srs)
        {
            osgEarth::Style        style;
            osgEarth::TextSymbol * textSymbol = style.getOrCreate<osgEarth::TextSymbol>();
            textSymbol->halo()                = osgEarth::Color(color);
            textSymbol->font()                = "./data/font/simkai.ttf"; // 设置支持中文的字体路径
            textSymbol->size()                = 20.0;                     // 根据需要设置字体大小
            textSymbol->encoding()            = osgEarth::TextSymbol::Encoding::ENCODING_UTF8;

            return new osgEarth::PlaceNode(osgEarth::GeoPoint(srs, lon, lat, alt), text, style);
        }
    }
    return nullptr;
}

osg::ref_ptr<osg::Node> LayerModule::addPlaceNode(std::string text, double lon, double lat, double alt /*= 0*/)
{
    osg::ref_ptr<osgEarth::MapNode> mapNode = NodeModule::getInstance()->getRootMapNode();
    if (mapNode)
    {
        osg::Image *           iconImage = osgDB::readImageFile("./data/placemark64.png");
        osgEarth::Style        style;
        osgEarth::TextSymbol * textSymbol = style.getOrCreate<osgEarth::TextSymbol>();
        textSymbol->halo()                = osgEarth::Color("5f5f5f");
        textSymbol->font()                = "./data/font/simkai.ttf"; // 设置支持中文的字体路径
        textSymbol->size()                = 20.0;                     // 根据需要设置字体大小
        textSymbol->encoding()            = osgEarth::TextSymbol::Encoding::ENCODING_UTF8;

        osgEarth::PlaceNode * placeNode = new osgEarth::PlaceNode(text, style, iconImage);

        const osgEarth::SpatialReference * srs = mapNode->getMapSRS();
        // const osgEarth::SpatialReference * srs = osgEarth::SpatialReference::get("wgs84");
        placeNode->setPosition(osgEarth::GeoPoint(srs, lon, lat, alt));
        return placeNode;
    }
    return nullptr;
}

osg::ref_ptr<osg::Node> LayerModule::addImage(const osg::Vec2d  lowerLeft,
                                              const osg::Vec2d  lowerRight,
                                              const osg::Vec2d  upperLeft,
                                              const osg::Vec2d  upperRight,
                                              const std::string path)
{
    osgEarth::ImageOverlay * imageOverlay = new osgEarth::ImageOverlay(NodeModule::getInstance()->getRootMapNode().get(),
                                                                       osgDB::readImageFile(path));
    imageOverlay->setCorners(lowerLeft, lowerRight, upperLeft, upperRight);
    imageOverlay->setAlpha(0.5);
    return imageOverlay;
}
