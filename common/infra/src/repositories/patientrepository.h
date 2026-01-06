#ifndef PATIENTREPOSITORY_H
#define PATIENTREPOSITORY_H

#include <common/infra/src/database/baserepository.h>
#include "common/infra/src/models/patient.h"


class PatientRepository : public BaseRepository
{
public:
    std::optional<int> create(const Patient& patient);
    std::optional<Patient> findById(int id);
    std::optional<QVector<Patient>> findByName(const QString& name);
    QVector<Patient> findAll();
    bool update(const Patient& patient);
    bool deleteById(int id);

    // 自定义查询
    QVector<Patient> findByPhone(const QString& phone);
    int count();

private:
    Patient mapFromQuery(QSqlQuery& query);
};

#endif // PATIENTREPOSITORY_H
