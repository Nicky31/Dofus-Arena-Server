#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QtCore>
#include "Coach.h"

struct Account
{
    unsigned int id;
    QString username;
    QString password;
    quint8 gmlevel;
    bool banned;
    bool online;
    int coach_id;
    Coach* coach;

    ~Account()
    {
        if(coach != 0)
            delete coach;
    }
};

#endif // ACCOUNT_H
