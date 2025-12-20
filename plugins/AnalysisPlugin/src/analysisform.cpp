#include "analysisform.h"
#include "ui_analysisform.h"
#include <qstyle.h>

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
