#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QString>
#include <QWidget>
#include <QtPlugin>

/**
 * @brief 插件接口基类
 * 所有插件都必须实现这个接口
 */
class IPlugin
{
public:
    virtual ~IPlugin() = default;

    /**
     * @brief 初始化插件
     * @return 成功返回true，失败返回false
     */
    virtual bool initialize() = 0;

    /**
     * @brief 反初始化插件，清理资源
     */
    virtual void uninitialize() = 0;

    /**
     * @brief 获取插件名称
     */
    virtual QString name() const = 0;

    /**
     * @brief 获取插件版本
     */
    virtual QString version() const = 0;

    /**
     * @brief 获取插件描述
     */
    virtual QString description() const = 0;

    /**
     * @brief 获取插件作者
     */
    virtual QString author() const = 0;

    /**
     * @brief 创建插件的主窗口部件
     * @return 插件的主窗口部件指针，如果插件没有UI则返回nullptr
     */
    virtual QWidget* createWidget() = 0;

    virtual QIcon icon() const = 0;          // 插件图标
    virtual QString displayName() const = 0; // 显示名称（用于按钮）

    /**
     * @brief 插件是否启用
     */
    virtual bool isEnabled() const = 0;

    /**
     * @brief 设置插件启用状态
     */
    virtual void setEnabled(bool enabled) = 0;
};

// 声明接口标识符，用于Qt的插件系统
Q_DECLARE_INTERFACE(IPlugin, "com.example.IPlugin/1.0")

#endif // IPLUGIN_H
