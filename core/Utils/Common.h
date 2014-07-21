#ifndef COMMON_H
#define COMMON_H

#include <QtCore>
#include <iostream>

using namespace std;

/*
 * Extracte le type de donnée numérique T du début du tableau et le renvoit
 * Considère que l'octet 'le plus significatif' est sur l'index 0
 */
template<class T>
T ExtractNum(QByteArray& datas)
{
    const quint8 size(sizeof(T)); // = Nombre d'octets du tableau à récupérer
    T value(0);

    for(int i = 0; i < size; ++i)
        value += ((T)datas.at(i)) << (8 * (size - (i + 1)));

    datas.remove(0, size);
    return value;
}

#endif // COMMON_H
