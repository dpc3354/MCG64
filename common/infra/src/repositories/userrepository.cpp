#include "userrepository.h"
#include <qsqlquery.h>

std::optional<int> UserRepository::create(const User &user)
{
    QSqlQuery query(database());
    query.prepare("INSERT INTO users (username, email) VALUES (:username, :email)");
    query.bindValue(":username", user.username());
    query.bindValue(":email", user.email());

    if (!executeQuery(query)) {
        return std::nullopt;
    }

    return query.lastInsertId().toInt();
}

std::optional<User> UserRepository::findById(int id)
{
    QSqlQuery query(database());
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (!executeQuery(query) || !query.next()) {
        return std::nullopt;
    }

    return mapFromQuery(query);
}

std::optional<QVector<User>> UserRepository::findByUsername(const QString &username)
{
    QVector<User> users;
    QSqlQuery query("SELECT * FROM users", database());

    if (!executeQuery(query)) {
        return users;
    }

    while (query.next()) {
        users.append(mapFromQuery(query));
    }

    return users;
}

QVector<User> UserRepository::findAll()
{
    QVector<User> users;
    QSqlQuery query("SELECT * FROM users", database());

    if (!executeQuery(query)) {
        return users;
    }

    while (query.next()) {
        users.append(mapFromQuery(query));
    }

    return users;
}

bool UserRepository::update(const User &user)
{
    QSqlQuery query(database());
    query.prepare("UPDATE users SET username = :username, email = :email WHERE id = :id");
    query.bindValue(":username", user.username());
    query.bindValue(":email", user.email());
    query.bindValue(":id", user.id());

    return executeQuery(query) && query.numRowsAffected() > 0;
}

bool UserRepository::deleteById(int id)
{
    QSqlQuery query(database());
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", id);

    return executeQuery(query) && query.numRowsAffected() > 0;
}

QVector<User> UserRepository::findByEmailDomain(const QString &domain)
{
    QVector<User> users;

    QSqlQuery query(database());
    query.prepare("SELECT * FROM users WHERE email = :domain");
    query.bindValue(":email", domain);

    if (!executeQuery(query))
        return users;

    while (query.next()) {
        users.append(mapFromQuery(query));
    }

    return users;
}

int UserRepository::count()
{
    QSqlQuery query("SELECT COUNT(*) FROM users", database());
    if (executeQuery(query) && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

User UserRepository::mapFromQuery(QSqlQuery &query)
{
    User user;
    user.setId(query.value("id").toInt());
    user.setUsername(query.value("username").toString());
    user.setEmail(query.value("email").toString());
    user.setCreatedAt(query.value("created_at").toDateTime());
    return user;
}
