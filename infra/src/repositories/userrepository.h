#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <infra/src/database/baserepository.h>

#include <infra/src/models/user.h>


class UserRepository : public BaseRepository
{
public:
    std::optional<int> create(const User& user);
    std::optional<User> findById(int id);
    std::optional<QVector<User>> findByUsername(const QString& username);
    QVector<User> findAll();
    bool update(const User& user);
    bool deleteById(int id);

    // 自定义查询
    QVector<User> findByEmailDomain(const QString& domain);
    int count();

private:
    User mapFromQuery(QSqlQuery& query);
};

#endif // USERREPOSITORY_H
