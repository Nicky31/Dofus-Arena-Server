#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtCore>
#include <QtNetwork>
#include "core/Logs/Log.h"
#include <cassert>
#include "core/Utils/Observer.h"

using namespace std;

class TCPServer : public QObject, public Observable
{
    Q_OBJECT

public:
    TCPServer();
    ~TCPServer();
    bool StartOn(QString ip, quint16 port);

    QTcpServer* GetServer() const;

public slots:
    void OnConnect();

private:
    QTcpServer* m_server;

};

#endif // TCPSERVER_H
