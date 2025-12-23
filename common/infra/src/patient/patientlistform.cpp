#include "patientlistform.h"
#include "ui_patientlistform.h"

PatientListForm::PatientListForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientListForm)
{
    ui->setupUi(this);
}

PatientListForm::~PatientListForm()
{
    delete ui;
}
