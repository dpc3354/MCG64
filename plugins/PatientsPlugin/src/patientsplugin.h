#ifndef PATIENTSPLUGIN_H
#define PATIENTSPLUGIN_H

#include "IPlugin.h"
#include <QWidget>

namespace Ui {
class PatientsPlugin;
}

class PatientsPlugin : public QWidget, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.IPlugin/1.0")
    Q_INTERFACES(IPlugin)

public:
    explicit PatientsPlugin(QWidget *parent = nullptr);
    ~PatientsPlugin();

    bool initialize() override;
    void uninitialize() override;
    QString name() const override;
    QString version() const override;
    QString description() const override;
    QString author() const override;
    QWidget* createWidget() override;  // 直接返回this
    QIcon icon() const override;
    QString displayName() const override;
    bool isEnabled() const override;
    void setEnabled(bool enabled) override;

private:
    Ui::PatientsPlugin *ui;

    bool m_enabled;
    bool m_initialized;  // 标记是否已初始化UI
};

#endif // PATIENTSPLUGIN_H
