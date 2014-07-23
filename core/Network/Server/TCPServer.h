#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtCore>
#include <QtNetwork>
#include <QList>
#include <iostream>
#include <cassert>
#include "game/Com/Session/ClientSession.h"
#include "core/Utils/Observer.h"

using namespace std;
class ClientSession;

class TCPServer : public QObject, public Observable
{
    Q_OBJECT

public:
    TCPServer();
    ~TCPServer();
    bool StartOn(QString ip, quint16 port);
    void RemoveSocket(ClientSession* socket);

    QTcpServer* GetServer() const;

public slots:
    void OnConnect();
    void OnDisconnection();

private:
    QTcpServer* m_server;
    QList<ClientSession*> m_clients;

};

#endif // TCPSERVER_H
