#ifndef MODELBUILD_H
#define MODELBUILD_H

#include <QList>
#include <osg/Node>

class ModelBuild
{
public:
    void addModel();
    void removeModel();

private:
    QList<osg::ref_ptr<osg::Node>> m_models;
};

#endif
