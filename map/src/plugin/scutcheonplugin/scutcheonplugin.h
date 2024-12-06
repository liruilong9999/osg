
#ifndef ScutcheonPlugin_H
#define ScutcheonPlugin_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <lib/pluginmanager/plugininterface.h>

class Scutcheon;
class ScutcheonPlugin : public QObject,
                        public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ScutcheonPlugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(PluginInterface)
public:
    explicit ScutcheonPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void addScutcheon();

private:
    QAction * m_actionScutcheon{nullptr}; // 添加日月星辰按钮
    //    QAction *    m_actionRemoveModel{nullptr}; // 生成模型按钮
    Scutcheon * m_Scutcheon{nullptr}; // 模型管理
};

#endif
