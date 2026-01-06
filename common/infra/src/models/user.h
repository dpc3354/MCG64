#ifndef USER_H
#define USER_H

#include <QDateTime>
#include <QString>


class User
{
public:
    User();
    User(int id, const QString& username, const QString& email);

    int id() const;
    QString username() const;
    QString email() const;
    QDateTime createdAt() const;

    void setId(int id);
    void setUsername(const QString& username);
    void setEmail(const QString& email);
    void setCreatedAt(const QDateTime& dt);

    bool isValid() const;
private:
    int m_id = -1;
    QString m_username;
    QString m_email;
    QDateTime m_createdAt;
};

#endif // USER_H
