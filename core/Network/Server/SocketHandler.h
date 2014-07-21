#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QtNetwork>
#include "core/Network/Packet/DAPacket.h"
#include "core/Logs/Log.h"
#include "iostream"

using namespace std;

class SocketHandler : public QObject
{
    Q_OBJECT

public:
    SocketHandler(QTcpSocket* socket);
    QString GetIp() const;
    inline QTcpSocket* GetSocket() const;

public slots:
    void OnRead();

protected:
    QTcpSocket* m_socket;
    quint16 m_packetSize;

    virtual void ProcessPacket(quint16 opcode, QByteArray packet) = 0;
    void SendPacket(DAPacket &packet) const;
};

#endif // SOCKETHANDLER_H
