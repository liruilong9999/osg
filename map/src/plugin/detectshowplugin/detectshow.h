#ifndef DETECTSHOW_H
#define DETECTSHOW_H

#include <string>
#include <QList>
#include <osgEarth/GeoTransform>

class DetectShow
{
public:
    void add();
    void remove();

private:
    QList<osg::ref_ptr<osgEarth::GeoTransform>> m_radarList;
    QList<osg::ref_ptr<osg::Node>>              m_modelList;
    QList<osg::ref_ptr<osg::Node>>              m_textList;
};

#endif
