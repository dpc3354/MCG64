#include "baserepository.h"
#include <qsqlerror.h>
#include <qsqlquery.h>

QSqlDatabase BaseRepository::database() const
{
    return DatabaseManager::instance().database();
}

bool BaseRepository::executeQuery(QSqlQuery &query) const
{
    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text();
        qWarning() << "SQL:" << query.lastQuery();
        return false;
    }
    return true;
}

BaseRepository::Transaction::Transaction(const QSqlDatabase &db) : m_db(db)
{
    m_success = m_db.transaction();
}

BaseRepository::Transaction::~Transaction()
{
    if (m_success && !m_committed) {
        m_db.rollback();
    }
}

bool BaseRepository::Transaction::commit()
{
    if (m_success) {
        m_committed = m_db.commit();
        return m_committed;
    }
    return false;
}
