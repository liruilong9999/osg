#ifndef EARTHWIDGET_H
#define EARTHWIDGET_H

#include <QMouseEvent>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <QObject>
#include <QVariant>
#include <osg/Vec3d>
#include <osgEarth/MapNode>
#include <osgEarth/GeodeticGraticule>

class EarthWidget : public osgQOpenGLWidget
{
    Q_OBJECT

public:
    EarthWidget(QWidget * parent = nullptr);
    ~EarthWidget();

public slots:
    void initializedSlots();

private:
    osgEarth::Util::GeodeticGraticule * m_pGraticule{nullptr};
    bool                                m_clicked{false};
};
#endif // EARTHWIDGET_H
