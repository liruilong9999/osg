#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osgText/Text>

#include <osgEarth/Sky>

#include <osgEarth/ShaderGenerator>
#include <osgEarth/GeoTransform>
#include <osgEarth/MapNode>
#include <osgEarth/ElevationQuery>

#include <module/nodemodule/nodemodule.h>
#include <module/viewermodule/viewermodule.h>

#include "scutcheon.h"

Scutcheon::Scutcheon()
{
}

osg::ref_ptr<osg::Node> Scutcheon::createScucheon()
{
    osg::ref_ptr<osgText::Text> textPtr = new osgText::Text;
    textPtr->setFont("./Map/3D/fonts/simsun.ttc");
    textPtr->setCharacterSize(14);
    QString context = QString::fromLocal8Bit("label");
    textPtr->setText(context.toStdString(), osgText::String::Encoding::ENCODING_UTF8);

    osg::ref_ptr<osg::Geode> geodePtr = new osg::Geode;
    geodePtr->addDrawable(textPtr);

    osg::ref_ptr<osg::AutoTransform> nodeAT = new osg::AutoTransform;                // 自动缩放矩阵
    nodeAT->setAutoRotateMode(osg::AutoTransform::AutoRotateMode::ROTATE_TO_SCREEN); // 始终朝向屏幕
    nodeAT->setAutoScaleToScreen(true);
    nodeAT->setMinimumScale(1.0); // 视角缩放的时候，字体的缩放比例变化 1.0-最小的缩放比例
    nodeAT->addChild(geodePtr);

    return nodeAT;
}
