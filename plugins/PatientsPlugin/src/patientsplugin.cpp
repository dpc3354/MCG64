#include "patientsplugin.h"
#include "IPlugin.h"
#include "ui_patientsplugin.h"

PatientsPlugin::PatientsPlugin(QWidget *parent)
    : QWidget(parent), ui(new Ui::PatientsPlugin), m_enabled(false),
      m_initialized(false) {
  ui->setupUi(this);
}

PatientsPlugin::~PatientsPlugin() { delete ui; }

bool PatientsPlugin::initialize()
{
    m_enabled = true;
    m_initialized = true;
    return true;
}

void PatientsPlugin::uninitialize() { m_enabled = false; }

QString PatientsPlugin::name() const { return "patient plugin"; }

QString PatientsPlugin::version() const
{
    return "1.0.0";
}

QString PatientsPlugin::description() const {
  return "";
}

QString PatientsPlugin::author() const
{
    return "";
}

QWidget *PatientsPlugin::createWidget() {
    return this;
}

QIcon PatientsPlugin::icon() const
{
    return QIcon::fromTheme("applications-system");
}

QString PatientsPlugin::displayName() const
{
    return "患者管理";
}

bool PatientsPlugin::isEnabled() const
{
    return m_enabled;
}

void PatientsPlugin::setEnabled(bool enabled)
{
    m_enabled = enabled;
}
