#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QMap>
#include <QPluginLoader>
#include <QDir>
#include "IPlugin.h"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);
        ~PluginManager();

    /**
     * @brief 从指定目录加载所有插件
     * @param pluginDir 插件目录路径
     * @return 成功加载的插件数量
     */
    int loadPlugins(const QString &pluginDir);

    /**
     * @brief 卸载所有插件
     */
    void unloadPlugins();

    /**
     * @brief 获取所有已加载的插件
     */
    QList<IPlugin*> getPlugins() const;

    /**
     * @brief 根据名称获取插件
     */
    IPlugin* getPlugin(const QString &name) const;

    /**
     * @brief 获取已加载的插件数量
     */
    int getPluginCount() const;

signals:
    /**
     * @brief 插件加载成功信号
     */
    void pluginLoaded(IPlugin *plugin);

    /**
     * @brief 插件卸载信号
     */
    void pluginUnloaded(const QString &pluginName);

    /**
     * @brief 插件加载失败信号
     */
    void pluginLoadFailed(const QString &fileName, const QString &errorString);

private:
    /**
     * @brief 加载单个插件
     */
    bool loadPlugin(const QString &filePath);

private:
    // 插件加载器映射表 <插件名称, QPluginLoader*>
    QMap<QString, QPluginLoader*> m_pluginLoaders;
    
    // 插件实例映射表 <插件名称, IPlugin*>
    QMap<QString, IPlugin*> m_plugins;

};

#endif // PLUGINMANAGER_H
