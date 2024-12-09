#include <osgDB/ReadFile>
#include <osgEarth/ShaderGenerator>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osg/MatrixTransform>

#include <module/nodemodule/nodemodule.h>
#include <osgDB/ReadFile>

#include <osgEarth/Style>
#include <osgEarth/TextSymbol>
#include <osgEarth/PlaceNode>

#include <osg/ShapeDrawable>
#include <osg/PolygonMode>

#include <random>

#include "featuremodule.h"

#define useLine_radar

// 创建雷达包络和扫描扇区，并应用逆时针旋转动画
osg::ref_ptr<osg::Group> FeatureModule::createRadar(double    radius,
                                                    osg::Vec4 envelopeColor,
                                                    osg::Vec4 scanColor,
                                                    double    minBeamAngle,
                                                    double    maxBeamAngle,
                                                    double    duration,
                                                    int       segments)
{
    osg::ref_ptr<osg::Group> group = new osg::Group();

    // 创建雷达包络球体
    osg::ref_ptr<osg::Sphere>        sphere        = new osg::Sphere(osg::Vec3(0.0, 0.0, 0.0), radius);
    osg::ref_ptr<osg::ShapeDrawable> shapeDrawable = new osg::ShapeDrawable(sphere);
    shapeDrawable->setColor(envelopeColor);
    shapeDrawable->setTessellationHints(new osg::TessellationHints);
    shapeDrawable->getTessellationHints()->setDetailRatio(segments / 10.0);

#ifdef useLine_radar
    osg::ref_ptr<osg::StateSet>    stateSet    = shapeDrawable->getOrCreateStateSet();
    osg::ref_ptr<osg::PolygonMode> polygonMode = new osg::PolygonMode;
    polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
    stateSet->setAttribute(polygonMode);
#endif
    osg::ref_ptr<osg::Geode> envelopeGeode = new osg::Geode();
    envelopeGeode->addDrawable(shapeDrawable.get());
    group->addChild(envelopeGeode.get());

    // 创建扫描扇区
    osg::ref_ptr<osg::Geometry>         geometry = new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array>        vertices = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array>        colors   = new osg::Vec4Array();
    osg::ref_ptr<osg::DrawElementsUInt> indices  = new osg::DrawElementsUInt(GL_TRIANGLE_FAN);

    // 扇区的中心点
    vertices->push_back(osg::Vec3(0.0, 0.0, 0.0));
    colors->push_back(scanColor);
    indices->push_back(0);

    // 计算扫描扇区的顶点
    int numSegments = segments;
    for (int i = 0; i <= numSegments; ++i)
    {
        double angle = osg::DegreesToRadians(minBeamAngle + (maxBeamAngle - minBeamAngle) * i / numSegments);
        double x     = radius * cos(angle);
        double z     = radius * sin(angle); // 在竖直方向（y-z平面）
        vertices->push_back(osg::Vec3(0.0, x, z));
        colors->push_back(scanColor);
        indices->push_back(i + 1);
    }

    geometry->setVertexArray(vertices.get());
    geometry->setColorArray(colors.get(), osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(indices.get());

    osg::ref_ptr<osg::Geode> scanGeode = new osg::Geode();
    scanGeode->addDrawable(geometry.get());

#ifndef useLine_radar
    osg::ref_ptr<osg::StateSet> stateSet = scanGeode->getOrCreateStateSet();
#else
    stateSet = scanGeode->getOrCreateStateSet();
#endif
    stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
    stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON); // 确保深度测试开启，以便正确处理透明度
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    // 创建MatrixTransform节点来应用动画
    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();
    transform->addChild(scanGeode.get());

    // 创建动画路径，实现逆时针旋转
    osg::ref_ptr<osg::AnimationPath> animationPath = new osg::AnimationPath();
    animationPath->setLoopMode(osg::AnimationPath::LOOP); // 无限循环

    int numSamples = 100;
    for (int i = 0; i <= numSamples; ++i)
    {
        double    t     = (double)i / (double)numSamples;
        double    angle = minBeamAngle + (360.0 - minBeamAngle) * t; // 逆时针旋转
        osg::Quat rotation(osg::DegreesToRadians(angle), osg::Vec3(0.0, 0.0, 1.0));
        animationPath->insert(t * duration, osg::AnimationPath::ControlPoint(osg::Vec3(0, 0, 0), rotation));
    }

    transform->setUpdateCallback(new osg::AnimationPathCallback(animationPath.get()));

    group->addChild(transform.get());

    return group;
}
