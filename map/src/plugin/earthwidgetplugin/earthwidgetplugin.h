﻿#ifndef EARTHWIDGETPLUGIN_H
#define EARTHWIDGETPLUGIN_H
#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>

class EarthWidget;
class EarthWidgetPlugin : public QObject,
                          public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "EarthWidgetPlugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit EarthWidgetPlugin(QObject * parent = nullptr);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void addHeight();

private:
    EarthWidget * m_earthWidget{nullptr};
    QAction *     m_addHeightAction{nullptr};
    bool          m_actHeightClicked{false};
};
#endif // EARTHWIDGET_H