
#include <module/modelmodule/modelmodule.h>
#include <module/nodemodule/nodemodule.h>
#include <osgText/Text>
#include <osg/MatrixTransform>
#include <osg/AutoTransform>
#include <osg/Vec4d>
#include <osg/Array>
#include <osg/Drawable>
#include <osg/BoundingSphere>

#include "modelbuild.h"

osg::ref_ptr<osg::Node> createScucheon()
{
    // 创建文本对象
    osg::ref_ptr<osgText::Text> textPtr = new osgText::Text;
    textPtr->setFont("./Map/3D/fonts/simsun.ttc");
    textPtr->setCharacterSize(14);
    QString context = QString::fromLocal8Bit(
        "雷达1\n"
        "经度：120°\n"
        "纬度：30度\n"
        ""
        ""
        "");
    textPtr->setText(context.toStdString(), osgText::String::Encoding::ENCODING_UTF8);
    textPtr->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0)); // 白色文本

    // 获取文本的边界框，用于计算背景矩形
    osg::BoundingBox bb = textPtr->getBoundingBox();
    osg::Vec3f       backgroundMin(bb.xMin() - 5.0f, bb.yMin() - 5.0f, 0.0f); // 适当调整背景矩形的大小
    osg::Vec3f       backgroundMax(bb.xMax() + 5.0f, bb.yMax() + 5.0f, 0.0f);

    // 创建背景矩形
    osg::ref_ptr<osg::Geometry>  background = new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> vertices   = new osg::Vec3Array(4);
    (*vertices)[0]                          = osg::Vec3(backgroundMin.x(), backgroundMin.y(), 0.0f); // 左下角
    (*vertices)[1]                          = osg::Vec3(backgroundMax.x(), backgroundMin.y(), 0.0f); // 右下角
    (*vertices)[2]                          = osg::Vec3(backgroundMax.x(), backgroundMax.y(), 0.0f); // 右上角
    (*vertices)[3]                          = osg::Vec3(backgroundMin.x(), backgroundMax.y(), 0.0f); // 左上角
    background->setVertexArray(vertices);

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 0.5f)); // 半透明黑色背景
    background->setColorArray(colors.get());
    background->setColorBinding(osg::Geometry::BIND_OVERALL);

    background->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

    osg::ref_ptr<osg::Geode> geodePtr = new osg::Geode;
    geodePtr->addDrawable(background); // 添加背景矩形
    geodePtr->addDrawable(textPtr);    // 添加文本

    // 创建 AutoTransform，确保文本和背景矩形始终面对屏幕
    osg::ref_ptr<osg::AutoTransform> autoTransform = new osg::AutoTransform;
    autoTransform->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN); // 始终朝向屏幕
    autoTransform->setPosition(osg::Vec3(0.0f, 0.0f, 0.0f));
    autoTransform->addChild(geodePtr);

    // 将 AutoTransform 添加到 MatrixTransform 以便控制相对位置
    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
    transform->setMatrix(osg::Matrix::translate(100, 100, 1000)); // 自定义的偏移量（右上方）
    transform->addChild(autoTransform);

    return transform;
}

void ModelBuild::addModel()
{
    osg::ref_ptr<osg::Group> modelNode = ModelModule::getInstance()->addModel(osg::Vec3d(120.0, 30.0, 10.0), 10, "./data/loopix/tree7.osgb");
    osg::ref_ptr<osg::Node>  scu       = createScucheon();
    modelNode->addChild(scu);
    NodeModule::getInstance()->getRootNode()->addChild(modelNode);
    m_models.push_back(modelNode);
}

void ModelBuild::removeModel()
{
    for (auto modelNode : m_models)
    {
        NodeModule::getInstance()->getRootNode()->removeChild(modelNode);
    }
}
