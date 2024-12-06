
#ifndef MOUSEPOINTINFOPLUGIN_H
#define MOUSEPOINTINFOPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>

class MousePointInfo;
class MousePointInfoPlugin : public QObject,
                             public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MousePointInfoPlugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit MousePointInfoPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;

private:
    //    QAction *    m_actionBuildModel{nullptr};  // 生成模型按钮
    //    QAction *    m_actionRemoveModel{nullptr}; // 生成模型按钮
    MousePointInfo * m_mousePointInfo{nullptr}; // 模型管理
};

#endif
