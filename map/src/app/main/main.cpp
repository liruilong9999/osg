#include <QApplication>
#include <QMenuBar>
#include <pluginmanager/pluginmanager.h>

#include <osgViewer/Viewer>
#include <osgEarth/Common>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    osgEarth::initialize();

    // 获取 IPluginView 实例
    PluginManager::GetInstance().loadAllPlugin();
    int ret = a.exec();
    PluginManager::GetInstance().unloadAllPlugin();

    return ret;
}
