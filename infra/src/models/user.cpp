#include "user.h"

User::User() {}

User::User(int id, const QString &username, const QString &email) : m_id(id), m_username(username), m_email(email)
{

}

int User::id() const
{
    return m_id;
}

QString User::username() const
{
    return m_username;
}

QString User::email() const
{
    return m_email;
}

QDateTime User::createdAt() const
{
    return m_createdAt;
}

void User::setId(int id)
{
    m_id = id;
}

void User::setUsername(const QString &username)
{
    m_username = username;
}

void User::setEmail(const QString &email)
{
    m_email = email;
}

void User::setCreatedAt(const QDateTime &dt)
{
    m_createdAt = dt;
}

bool User::isValid() const
{
    return m_id > 0 && !m_username.isEmpty();
}
