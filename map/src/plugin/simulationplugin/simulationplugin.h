
#ifndef MODELBUILDPLUGIN_H
#define MODELBUILDPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>
#include <QTimer>

class SimulationPlugin : public QObject,
                         public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "simulationplugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit SimulationPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;

public slots:
    void addModelSlot();
    void removeModelSlot();
    void simulationSlot();

private:
    QAction * m_actionBuildModel{nullptr};  // 生成模型按钮
    QAction * m_actionRemoveModel{nullptr}; // 生成模型按钮
    QTimer *  m_timer{nullptr};
};

#endif
