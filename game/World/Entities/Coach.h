#ifndef COACH_H
#define COACH_H

#include <QtCore>

struct Coach
{
    unsigned int id;
    QString name;
    quint8 skinColorIndex;
    quint8 hairColorIndex;
    unsigned char sex;
};

#endif // COACH_H
