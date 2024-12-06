
#ifndef WEATHERPLUGIN_H
#define WEATHERPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>

class Weather;
class WeatherPlugin : public QObject,
                      public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "WeatherPlugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit WeatherPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void addWeather();

private:
    QAction * m_actionWeather{nullptr}; // 添加日月星辰按钮
    //    QAction *    m_actionRemoveModel{nullptr}; // 生成模型按钮
    Weather * m_Weather{nullptr}; // 模型管理
};

#endif
