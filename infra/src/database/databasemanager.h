#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>


class DatabaseManager
{
public:
    static DatabaseManager& instance();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    bool initialize(const QString &dbPath);
    QSqlDatabase database() const;
    bool isConnected() const;

private:
    DatabaseManager() = default;
    ~DatabaseManager();

    bool createTables();
    bool runMigrations();

    bool m_initialized = false;
    QSqlDatabase m_database;
};

#endif // DATABASEMANAGER_H
