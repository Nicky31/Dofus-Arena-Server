#ifndef COACHDAO_H
#define COACHDAO_H

#include "core/Databases/DatabaseConnection.h"
#include "game/World/Entities/Coach.h"

class CoachDAO
{
public:
    CoachDAO(DatabaseConnection* conn) : m_connection(conn)
    { }

    Coach* Get(int id)
    {
        QSqlQuery query;
        try
        {
            query = m_connection->PQuery("SELECT * FROM `coachs` WHERE `id` = ?",
                                         QVariantList() << id);
        } catch(std::runtime_error err)
        {
            Log::Instance()->Write(ERROR_LOG, err.what());
            return 0;
        }
        if(!query.first())
            return 0;

        Coach* coach = new Coach;
        coach->id             = id;
        coach->name           = VALUE(query, "name").toString();
        coach->hairColorIndex = VALUE(query, "hairColor").toInt();
        coach->skinColorIndex = VALUE(query, "skinColor").toInt();
        coach->sex            = (unsigned char)VALUE(query, "sex").toInt();

        return coach;
    }

    int Create(Coach* const coach)
    {
        QSqlQuery query;
        try
        {
            query = m_connection->PQuery("INSERT INTO `coachs`(`name`, `skinColor`, `hairColor`, `sex`) VALUES (?,?,?,?);",
                                         QVariantList() << coach->name << coach->skinColorIndex << coach->hairColorIndex << coach->sex);
        }
        catch(std::runtime_error err)
        {
            Log::Instance()->Write(ERROR_LOG, err.what());
            return -1;
        }
        if(!query.lastInsertId().isValid())
        {
            Log::Instance()->Write(ERROR_LOG, "Impossible de recuperer le lastInsertId : ceci est peut etre du a un probleme de compatibilite.");
            return -1;
        }

        return query.lastInsertId().toInt();
    }

    bool CheckName(QString name)
    {
        QSqlQuery query;
        try
        {
            query = m_connection->PQuery("SELECT COUNT(id) AS count FROM coachs WHERE name = ?", QVariantList() << name);
        }
        catch(std::runtime_error err)
        {
            Log::Instance()->Write(ERROR_LOG, err.what());
            return false;
        }
        if(!query.first())
            return false;

        return VALUE(query, "count").toInt() == 0;
    }

private:
    DatabaseConnection* m_connection;
};

#endif // COACH²_H
