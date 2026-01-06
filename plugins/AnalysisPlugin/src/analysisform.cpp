#include "analysisform.h"
#include "ui_analysisform.h"
#include <pluginmanager.h>
#include <qdialog.h>
#include <qstyle.h>
#include <QMessageBox>

AnalysisForm::AnalysisForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnalysisForm)
{
    ui->setupUi(this);
}

AnalysisForm::~AnalysisForm()
{
    delete ui;
}

bool AnalysisForm::initialize()
{
    m_enabled = true;
    m_initialized = true;
    return true;
}

void AnalysisForm::uninitialize()
{
    m_enabled = false;
}

QString AnalysisForm::name() const
{
    return "analysis plugin";
}

QString AnalysisForm::version() const
{
    return "1.0.0";
}

QString AnalysisForm::description() const
{
    return "";
}

QString AnalysisForm::author() const
{
    return "";
}

QWidget *AnalysisForm::createWidget()
{
    return this;
}

bool AnalysisForm::isOnIconBar() const
{
    return true;
}

QIcon AnalysisForm::icon() const
{
    return style()->standardIcon(QStyle::SP_FileLinkIcon);
}

QString AnalysisForm::displayName() const
{
    return "分析管理";
}

bool AnalysisForm::isEnabled() const
{
    return m_enabled;
}

void AnalysisForm::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

void AnalysisForm::showEvent(QShowEvent *event)
{
    // 检查报告插件是否存在
    if (PluginManager::instance()->hasPlugin("Report Plugin")) {
        qDebug() << "Report plugin detected, display report button";

        connect(ui->pushButton_3, &QPushButton::clicked, [this]() {
            // 获取报告插件
            IPlugin* reportPlugin = PluginManager::instance()->getPlugin("Report Plugin");
            if (reportPlugin) {
                // 创建并显示报告对话框
                QDialog* reportDialog = reportPlugin->createDialog(this);
                if (reportDialog) {
                    reportDialog->exec();
                    delete reportDialog;
                } else {
                    QMessageBox::warning(this, "错误", "无法创建报告界面");
                }
            }
        });
    } else {
        qDebug() << "Report plugin not available";
        ui->pushButton_3->hide();
    }
    QWidget:show();
}
