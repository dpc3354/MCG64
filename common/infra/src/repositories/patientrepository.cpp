#include "patientrepository.h"
#include <qsqlquery.h>

std::optional<int> PatientRepository::create(const Patient &patient)
{
    QSqlQuery query(database());
    query.prepare("INSERT INTO patients (name, age, phone) VALUES (:name, :age, :phone)");
    query.bindValue(":name", patient.name());
    query.bindValue(":age", patient.age());
    query.bindValue("phone", patient.phone());

    if (!executeQuery(query)) {
        return std::nullopt;
    }

    return query.lastInsertId().toInt();
}

std::optional<Patient> PatientRepository::findById(int id)
{
    QSqlQuery query(database());
    query.prepare("SELECT * FROM patients WHERE id = :id");
    query.bindValue(":id", id);

    if (!executeQuery(query) || !query.next()) {
        return std::nullopt;
    }

    return mapFromQuery(query);
}

std::optional<QVector<Patient> > PatientRepository::findByName(const QString &name)
{

}

QVector<Patient> PatientRepository::findAll()
{

}

bool PatientRepository::update(const Patient &patient)
{

}

bool PatientRepository::deleteById(int id)
{

}

QVector<Patient> PatientRepository::findByPhone(const QString &phone)
{

}

int PatientRepository::count()
{

}

Patient PatientRepository::mapFromQuery(QSqlQuery &query)
{
    Patient patient;;
    patient.setId(query.value("id").toInt());
    patient.setName(query.value("name").toString());
    patient.setAge(query.value("age").toInt());
    patient.setPhone(query.value("phone").toString());
    patient.setCreateAt(query.value("created_at").toDateTime());
    return patient;
}
