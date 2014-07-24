#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection(QString host, QString user, QString password, QString dbName, int port)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(host);
    m_db.setUserName(user);
    m_db.setPassword(password);
    m_db.setDatabaseName(dbName);
    m_db.setPort(port);
}

bool DatabaseConnection::Open()
{
    if(!m_db.open())
    {
        Log::Instance()->Write(ERROR_LOG, "MySQl error : " + m_db.lastError().text());
        return false;
    }

    return true;
}

QSqlQuery DatabaseConnection::PQuery(QString queryStr, QVariantList args)
{
    if(!m_db.isOpen())
        throw std::runtime_error("Database : Tentative de requete sur une connexion non ouverte : " + queryStr.toStdString()
                                 + " : "  + m_db.lastError().text().toLatin1().constData());

    QSqlQuery query(m_db);
    query.prepare(queryStr);

    while (!args.isEmpty())
        query.addBindValue(args.takeFirst());

    if(!query.exec())
        throw std::runtime_error("Database : Erreur lors de l'execution de \"" + queryStr.toStdString() + "\" : "
                                 + query.lastError().text().toLatin1().data());

    return query;
}

QSqlQuery DatabaseConnection::Query(QString queryStr)
{
    if(!m_db.isOpen())
        throw std::runtime_error("Database : Tentative de requete sur une connexion non ouverte : " + queryStr.toStdString()
                                 + " : "  + m_db.lastError().text().toLatin1().data());

    QSqlQuery query(m_db);
    if(!query.exec(queryStr))
        throw std::runtime_error("Database : Erreur lors de l'execution de \"" + queryStr.toStdString() + "\" : "
                                 + query.lastError().text().toLatin1().data());

    return query;
}
