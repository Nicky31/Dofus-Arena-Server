#include "DAOFactory.h"

DatabaseConnection* DAOFactory::dynDB = 0;
DatabaseConnection* DAOFactory::worldDB = 0;

AccountDAO* DAOFactory::accountDAO = 0;
CoachDAO* DAOFactory::coachDAO = 0;
