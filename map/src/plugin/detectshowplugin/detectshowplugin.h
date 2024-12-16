
#ifndef DETECTSHOWPLUGIN_H
#define DETECTSHOWPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <common/IPlugin.h>

class DetectShow;
class DetectShowPlugin : public QObject,
                         public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "modelbuildplugin" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(IPlugin)
public:
    explicit DetectShowPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void addSlot();
    void removeSlot();
	Q_INVOKABLE void showDetect(const QVariant & var);

private:
    QAction *    m_actionAdd{nullptr};    // 生成模型按钮
    QAction *    m_actionRemove{nullptr}; // 生成模型按钮
    DetectShow * m_detectShow{nullptr};   // 模型管理
};

#endif
