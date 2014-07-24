#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include "core/Logs/Log.h"
#include <stdexcept>

// Raccourcit la syntaxe pour récupérer une colonne de la ligne courante
#define VALUE(query, field) query.value(query.record().indexOf(field))

class DatabaseConnection
{
public:
    DatabaseConnection(QString host, QString user, QString password, QString dbName, int port);
    bool Open();
    // throw runtime_error :
    QSqlQuery PQuery(QString queryStr, QVariantList args);
    // throw runtime_error :
    QSqlQuery Query(QString queryStr);

private:
    QSqlDatabase m_db;
};

#endif // DATABASECONNECTION_H
