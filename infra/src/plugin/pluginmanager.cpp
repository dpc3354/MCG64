#include "pluginmanager.h"

PluginManager::PluginManager(QObject *parent)
    : QObject{parent}
{}

PluginManager::~PluginManager()
{
    unloadPlugins();
}

int PluginManager::loadPlugins(const QString &pluginDir)
{
    QDir dir(pluginDir);
    if (!dir.exists()) {
        qWarning() << "Plugin directory does not exist:" << pluginDir;
        return 0;
    }

    int loadedCount = 0;
    
    // 根据平台设置插件文件过滤器
#ifdef Q_OS_WIN
    QStringList filters;
    filters << "*.dll";
    dir.setNameFilters(filters);
#elif defined(Q_OS_LINUX)
    QStringList filters;
    filters << "*.so";
    dir.setNameFilters(filters);
#elif defined(Q_OS_MAC)
    QStringList filters;
    filters << "*.dylib";
    dir.setNameFilters(filters);
#endif

    QFileInfoList fileList = dir.entryInfoList(QDir::Files);
    
    for (const QFileInfo &fileInfo : fileList) {
        if (loadPlugin(fileInfo.absoluteFilePath())) {
            loadedCount++;
        }
    }

    qInfo() << "Loaded" << loadedCount << "plugins from" << pluginDir;
    return loadedCount;
}

bool PluginManager::loadPlugin(const QString &filePath)
{
    QPluginLoader *loader = new QPluginLoader(filePath, this);
    QObject *pluginObject = loader->instance();

    if (!pluginObject) {
        QString errorMsg = loader->errorString();
        qWarning() << "Failed to load plugin:" << filePath << "-" << errorMsg;
        emit pluginLoadFailed(filePath, errorMsg);
        delete loader;
        return false;
    }

    IPlugin *plugin = qobject_cast<IPlugin*>(pluginObject);
    if (!plugin) {
        qWarning() << "Plugin does not implement IPlugin interface:" << filePath;
        loader->unload();
        delete loader;
        return false;
    }

    // 初始化插件
    if (!plugin->initialize()) {
        qWarning() << "Plugin initialization failed:" << plugin->name();
        loader->unload();
        delete loader;
        return false;
    }

    QString pluginName = plugin->name();
    
    // 检查是否已经加载了同名插件
    if (m_plugins.contains(pluginName)) {
        qWarning() << "Plugin with same name already loaded:" << pluginName;
        plugin->uninitialize();
        loader->unload();
        delete loader;
        return false;
    }

    // 保存插件信息
    m_pluginLoaders.insert(pluginName, loader);
    m_plugins.insert(pluginName, plugin);

    qInfo() << "Plugin loaded successfully:" << pluginName 
            << "version:" << plugin->version();
    
    emit pluginLoaded(plugin);
    return true;
}

void PluginManager::unloadPlugins()
{
    // 反初始化所有插件
    for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it) {
        IPlugin *plugin = it.value();
        if (plugin) {
            plugin->uninitialize();
            qInfo() << "Plugin uninitialized:" << it.key();
        }
    }

    // 卸载所有插件
    for (auto it = m_pluginLoaders.begin(); it != m_pluginLoaders.end(); ++it) {
        QString pluginName = it.key();
        QPluginLoader *loader = it.value();
        
        if (loader) {
            loader->unload();
            delete loader;
            emit pluginUnloaded(pluginName);
        }
    }

    m_plugins.clear();
    m_pluginLoaders.clear();
    
    qInfo() << "All plugins unloaded";
}

QList<IPlugin*> PluginManager::getPlugins() const
{
    return m_plugins.values();
}

IPlugin* PluginManager::getPlugin(const QString &name) const
{
    return m_plugins.value(name, nullptr);
}

int PluginManager::getPluginCount() const
{
    return m_plugins.size();
}
