#include "infra/src/plugin/pluginmanager.h"
#include "infra/src/database/databasemanager.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setOrganizationName("Example");
    app.setApplicationName("Qt Plugin Framework");
    app.setApplicationVersion("1.0.0");

    // 创建插件管理器
    PluginManager pluginManager;

    // 创建并显示主窗口
    MainWindow mainWindow;
    mainWindow.setPluginManager(&pluginManager);

    // 获取插件目录路径
    QString pluginDir = QCoreApplication::applicationDirPath() + "/plugins";
    QDir dir(pluginDir);
    if (!dir.exists()) {
        dir.mkpath(pluginDir);
    }

    qInfo() << "Loading plugins from:" << pluginDir;

    // 加载插件
    int loadedCount = pluginManager.loadPlugins(pluginDir);
    qInfo() << "Total plugins loaded:" << loadedCount;

    // // 初始化数据库
    if (!DatabaseManager::instance().initialize("mcg.db")) {
        return -1;
    }


    mainWindow.show();
    return app.exec();
}
