#ifndef ACCOUNTDAO_H
#define ACCOUNTDAO_H

#include "core/Databases/DatabaseConnection.h"
#include "game/World/Entities/Account.h"

class AccountDAO
{
public:
    AccountDAO(DatabaseConnection* conn) : m_connection(conn)
    { }
    bool Update(Account* const acc)
    {
        QSqlQuery query;
        try
        {
            query = m_connection->PQuery("UPDATE `accounts` SET `gmlevel` = ?, `banned` = ?, `online` = ?, `coach_id` = ? WHERE `id` = ?",
                                         QVariantList() << acc->gmlevel << (int)acc->banned << (int)acc->online << acc->coach_id << acc->id);
        } catch(std::runtime_error err)
        {
            Log::Instance()->Write(ERROR_LOG, err.what());
            return false;
        }

        return query.isActive();
    }
    Account* Get(QString accountName, QString password)
    {
        QSqlQuery query;
        try
        {
            query = m_connection->PQuery("SELECT * FROM `accounts` WHERE `account` = ? AND `password` = ?",
                                         QVariantList() << accountName << password);
        } catch(std::runtime_error err)
        {
            Log::Instance()->Write(ERROR_LOG, err.what());
            return 0;
        }
        if(!query.first())
            return 0;

        Account* acc = new Account;
        acc->id       = VALUE(query, "id").toUInt();
        acc->username = VALUE(query, "account").toString();
        acc->password = VALUE(query, "password").toString();
        acc->gmlevel  = VALUE(query, "gmlevel").toUInt();
        acc->banned   = VALUE(query, "banned").toInt() == 1;
        acc->online   = VALUE(query, "online").toInt() == 1;
        acc->coach_id = VALUE(query, "coach_id").toInt();
        acc->coach    = 0;

        return acc;
    }

private:
    DatabaseConnection* m_connection;

};

#endif // ACCOUNTDAO_H
