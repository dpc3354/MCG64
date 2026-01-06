#include "patient.h"

Patient::Patient() {}

Patient::Patient(int id, const QString &name, int age, const QString &phone) : m_id(id), m_name(name), m_age(age), m_phone(phone)
{
}

int Patient::id() const
{
    return m_id;
}

QString Patient::name() const
{
    return m_name;
}

int Patient::age() const
{
    return m_age;
}

QString Patient::phone() const
{
    return m_phone;
}

QDateTime Patient::createdAt() const
{
    return m_createdAt;
}

void Patient::setId(int id)
{
    m_id = id;
}

void Patient::setName(const QString &name)
{
    m_name = name;
}

void Patient::setAge(int age)
{
    m_age = age;
}

void Patient::setPhone(const QString phone)
{
    m_phone = phone;
}

void Patient::setCreateAt(const QDateTime &dt)
{
    m_createdAt = dt;
}

bool Patient::isValid() const
{
    return m_id > 0 && !m_name.isEmpty();
}


