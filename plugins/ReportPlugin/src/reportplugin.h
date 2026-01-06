#ifndef REPORTPLUGIN_H
#define REPORTPLUGIN_H

#include <IPlugin.h>



class ReportPlugin : public QObject ,public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.IPlugin/1.0")
    Q_INTERFACES(IPlugin)

public:
    ReportPlugin();
    ~ReportPlugin() = default;

    bool initialize() override;
    void uninitialize() override;
    QString name() const override;
    QString version() const override;
    QString description() const override;
    QString author() const override;
    QWidget* createWidget() override;  // 直接返回nullptr
    QDialog* createDialog(QWidget* parent = nullptr) override;
    bool isOnIconBar() const override;
    QIcon icon() const override;
    QString displayName() const override;
    bool isEnabled() const override;
    void setEnabled(bool enabled) override;

private:
    bool m_enabled;
    bool m_initialized;  // 标记是否已初始化UI
};

#endif // REPORTPLUGIN_H
