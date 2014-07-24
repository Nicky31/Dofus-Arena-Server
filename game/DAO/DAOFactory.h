#ifndef DAOFACTORY_H
#define DAOFACTORY_H

#include "AccountDAO.h"
#include "CoachDAO.h"
#include <cassert>

class DAOFactory
{
public:
    static void Close()
    {
        // If nécessaire au cas d'un crash au lancement, appellant DAOFactory::Close sans que tous les DAO soient instanciés
        if(accountDAO != 0)
            delete accountDAO;
        if(coachDAO != 0)
            delete coachDAO;
    }

    static void SetDynDB(DatabaseConnection* dyndb)
    {
        dynDB = dyndb;
    }
    static void SetWorldDB(DatabaseConnection* worlddb)
    {
        worldDB = worlddb;
    }

    static AccountDAO* GetAccountDAO()
    {
        if(accountDAO == 0)
        {
            assert(dynDB != 0 && "Construction de AccountDAO sans que (DatabaseConnection*)dynDB soit defini");
            accountDAO = new AccountDAO(dynDB);
        }

        return accountDAO;
    }

    static CoachDAO* GetCoachDAO()
    {
        if(coachDAO == 0)
        {
            assert(dynDB != 0 && "Construction de CoachDAO sans que (DatabaseConnection*)dynDB soit defini");
            coachDAO = new CoachDAO(dynDB);
        }

        return coachDAO;
    }

private:
    static DatabaseConnection* dynDB;
    static DatabaseConnection* worldDB;

    static AccountDAO* accountDAO;
    static CoachDAO* coachDAO;
};

#endif // DAOFACTORY_H
