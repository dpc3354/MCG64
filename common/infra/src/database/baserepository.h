#ifndef BASEREPOSITORY_H
#define BASEREPOSITORY_H

#include <qsqldatabase.h>
#include "databasemanager.h"

class BaseRepository
{
public:
    BaseRepository();

protected:
    QSqlDatabase database() const;
    bool executeQuery(QSqlQuery& query) const;

    class Transaction {
    public:
        explicit Transaction(const QSqlDatabase& db);
        ~Transaction();
        bool commit();
    private:
        QSqlDatabase m_db;
        bool m_success = false;
        bool m_committed = false;
    };
};

#endif // BASEREPOSITORY_H
