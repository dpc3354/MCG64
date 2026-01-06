#ifndef ANALYSISFORM_H
#define ANALYSISFORM_H

#include "IPlugin.h"
#include <QWidget>

namespace Ui {
class AnalysisForm;
}

class AnalysisForm : public QWidget, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.IPlugin/1.0")
    Q_INTERFACES(IPlugin)

public:
    explicit AnalysisForm(QWidget *parent = nullptr);
    ~AnalysisForm();

    bool initialize() override;
    void uninitialize() override;
    QString name() const override;
    QString version() const override;
    QString description() const override;
    QString author() const override;
    QWidget* createWidget() override;  // 直接返回this
    bool isOnIconBar() const override;
    QIcon icon() const override;
    QString displayName() const override;
    bool isEnabled() const override;
    void setEnabled(bool enabled) override;

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::AnalysisForm *ui;

    bool m_enabled;
    bool m_initialized;  // 标记是否已初始化UI
};

#endif // ANALYSISFORM_H
