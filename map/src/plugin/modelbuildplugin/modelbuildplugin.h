
#ifndef MODELBUILDPLUGIN_H
#define MODELBUILDPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>

class ModelBuild;
class DetectShowPlugin : public QObject,
                         public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "modelbuildplugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit DetectShowPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void addModelSlot();
    void removeModelSlot();

private:
    QAction *    m_actionBuildModel{nullptr};  // 生成模型按钮
    QAction *    m_actionRemoveModel{nullptr}; // 生成模型按钮
    ModelBuild * m_modelCtrl{nullptr};         // 模型管理
};

#endif
