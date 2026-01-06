#include "databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::initialize(const QString& dbPath)
{
    if (m_initialized)
        return true;

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbPath);

    if (!m_database.open()) {
        qCritical() << "Database open failed:" << m_database.lastError().text();
        return false;
    }

    // 启用外键支持
    QSqlQuery query(m_database);
    query.exec("PRAGMA foreign_keys = ON");

    if (!createTables()) {
        return false;
    }

    m_initialized = true;
    return true;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_database;
}

bool DatabaseManager::isConnected() const
{

}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen())
        m_database.close();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query(m_database);

    // 用户表
    QString userTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            email TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (!query.exec(userTable)) {
        qCritical() << "Create users table failed:" << query.lastError();
        return false;
    }

    QString patientTable = R"(
        CREATE TABLE IF NOT EXISTS patients (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            age INT,
            phone TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (!query.exec(patientTable)) {
        qCritical() << "Create patients table failed:" << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::runMigrations()
{

}
