#ifndef MAPMODULE_H
#define MAPMODULE_H

#include <vector>
#include <osgEarth/ImageLayer>

#include <common/TSingleton.hpp>

#include "mapmodule_global.h"

enum class MapDataType
{
    Type_Tiff,
    Type_XYZ
};

struct LayerInfo
{
    bool                               isShowState{true};   // 图层显示状态
    unsigned int                       layerNumber{0};      // 图层当前的图层层数
    std::string                        layerUrl;            // 地图数据Url
    MapDataType                        layerType;           // 地图类型
    osg::ref_ptr<osgEarth::ImageLayer> imageLayer{nullptr}; // 当前图层
};

class MAPMODULE_EXPORT MapModule : public TSingleton<MapModule>
{
    friend class TSingleton<MapModule>;

public:
    // 初始化
    void init();
    // 读取配置文件数据，并且添加到地图上
    void addConfigData();
    // 添加tiff图层
    void addGeoTiff(LayerInfo & layerInfo);
    // 添加MBTiles图层
    void addMBTiles(LayerInfo & layerInfo);
    // 添加TMS图层
    void addTMS(LayerInfo & layerInfo);
    // 添加WMS图层
    void addWMS(LayerInfo & layerInfo);
    // 添加XYZ图层，即{z}/{x}/{y}.png
    void addXYZ(LayerInfo & layerInfo);
    // 进行图层组合
    // void addComposite();
    // 添加热力图图层
    void addContour(LayerInfo & layerInfo);

    // 添加高程数据
    osg::Node * addHeight();

    // 获取图层列表，用于外部rootMap调用
    std::vector<LayerInfo> & getLayerVec();

private:
    MapModule();
    std::vector<LayerInfo> m_layerVec;
};

#endif
