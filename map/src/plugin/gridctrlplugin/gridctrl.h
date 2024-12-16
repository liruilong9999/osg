#ifndef GRIDCTRL_H
#define GRIDCTRL_H

#include <QObject>
#include <osgEarth/GeodeticGraticule>

class GridCtrl
{
public:
    void showOrHideGrid();

private:
    osgEarth::Util::GeodeticGraticule * m_pGraticule{nullptr};
    bool                                m_clicked{false};
};
#endif // PLUGINA_H
