#include "reportplugin.h"
#include "reportdialog.h"
#include <qapplication.h>
#include <qstyle.h>

ReportPlugin::ReportPlugin() {}

bool ReportPlugin::initialize()
{
    m_enabled = true;
    m_initialized = true;
    return true;
}

void ReportPlugin::uninitialize()
{
    m_enabled = false;
}

QString ReportPlugin::name() const {
    return "Report Plugin";
}

QString ReportPlugin::version() const
{
    return "1.0.0";
}

QString ReportPlugin::description() const {
    return "";
}

QString ReportPlugin::author() const
{
    return "";
}

QWidget *ReportPlugin::createWidget() {
    return nullptr;
}

QDialog *ReportPlugin::createDialog(QWidget *parent)
{
    return new ReportDialog(parent);
}

bool ReportPlugin::isOnIconBar() const
{
    return false;
}

QIcon ReportPlugin::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView);
}

QString ReportPlugin::displayName() const
{
    return "生成报告";
}

bool ReportPlugin::isEnabled() const
{
    return m_enabled;
}

void ReportPlugin::setEnabled(bool enabled)
{
    m_enabled = enabled;
}



