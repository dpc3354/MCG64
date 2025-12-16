#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QListWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include "infra/src/plugin/pluginmanager.h"

QT_BEGIN_NAMESPACE

class QVBoxLayout;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPluginManager(PluginManager *manager);

private slots:
    /**
     * @brief 处理插件加载事件
     */
    void onPluginLoaded(IPlugin *plugin);

    /**
     * @brief 处理插件卸载事件
     */
    void onPluginUnloaded(const QString &pluginName);

    /**
     * @brief 处理插件选择事件
     */
    void onPluginSelected(QListWidgetItem *item);

    void onSidebarButtonClicked(int id);

private:
    void addPluginToSidebar(IPlugin *plugin);

    Ui::MainWindow *ui;

    PluginManager *m_pluginManager;

    QWidget *centralWidget;
    QWidget *sidebarWidget;       // 左侧按钮栏容器
    QVBoxLayout *sidebarLayout;   // 左侧布局
    QStackedWidget *contentStack; // 右侧内容堆栈
    QButtonGroup *buttonGroup;    // 按钮组管理

    QMap<int, IPlugin *> pluginMap; // 按钮ID -> 插件映射
    int nextButtonId;               // 下一个按钮ID
};
#endif // MAINWINDOW_H
