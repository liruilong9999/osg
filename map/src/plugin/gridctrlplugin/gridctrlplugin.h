
#ifndef GRIDCTRLPLUGIN_H
#define GRIDCTRLPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QAction>
#include <common/IPlugin.h>

class GridCtrl;
class GridCtrlPlugin : public QObject,
                       public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugina" FILE "plugin_info.json") // QT5.0 引入
    Q_INTERFACES(IPlugin)
public:
    explicit GridCtrlPlugin(QObject * parent = 0);
    virtual QString getname() override;
    virtual bool    init() override;
    virtual bool    clean() override;
public slots:
    void gridSlots();

private:
    QAction *  m_action{nullptr}; // 控制网格显隐按钮
    GridCtrl * m_grid{nullptr};   // 网格类
};
#endif // PLUGINA_H
