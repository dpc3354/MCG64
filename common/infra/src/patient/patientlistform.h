#ifndef PATIENTLISTFORM_H
#define PATIENTLISTFORM_H

#include <QWidget>

namespace Ui {
class PatientListForm;
}

class PatientListForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientListForm(QWidget *parent = nullptr);
    ~PatientListForm();

private:
    Ui::PatientListForm *ui;
};

#endif // PATIENTLISTFORM_H
