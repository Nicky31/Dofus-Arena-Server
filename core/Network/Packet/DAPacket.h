#ifndef DAPACKET_H
#define DAPACKET_H

#include <QtCore>
#include "iostream"

using namespace std;

class DAPacket
{
public:
    DAPacket(quint16 opcode, QByteArray datas = NULL);
    QByteArray GetDatas(bool header = true);
    quint16 GetOpcode() const;

    template <class T>
    DAPacket& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
    }
    // L'opérateur QDataStream::<<(const char* value) formate la chaine (taille sur 4 octets en début de chaine + OxOO en fin)
    DAPacket& operator<<(const char* value)
    {
        return (*this << QString(value));
    }

    DAPacket& operator<<(QString const& value)
    {
        m_stream.writeRawData(value.toLatin1().data(), value.toLatin1().size());
        return *this;
    }


private:
    quint16 m_opcode;
    QByteArray m_datas;
    QDataStream m_stream;

    QByteArray GetHeader();
};

#endif
