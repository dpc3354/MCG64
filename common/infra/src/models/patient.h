#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <qdatetime.h>


class Patient
{
public:
    Patient();
    Patient(int id, const QString& name, int age, const QString& phone);

    int id() const;
    QString name() const;
    int age() const;
    QString phone() const;
    QDateTime createdAt() const;

    void setId(int id);
    void setName(const QString& name);
    void setAge(int age);
    void setPhone(const QString phone);
    void setCreateAt(const QDateTime& dt);

    bool isValid() const;

private:
    int m_id = -1;
    QString m_name;
    int m_age;
    QString m_phone;
    QDateTime m_createdAt;
};

#endif // PATIENT_H
