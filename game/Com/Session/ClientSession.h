#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include "core/Network/Server/SocketHandler.h"
#include "core/Network/Server/TCPServer.h"
#include "game/Com/Opcodes/OpcodesMgr.h"
#include "game/Configs/Configs.h"
#include "core/Utils/Common.h"
#include "iostream"

using namespace std;

struct AccountInfos
{
    QString account;
    QString password;
    bool authentified;

    AccountInfos() : account(""), password(""), authentified(false)
    {}
};

class ClientSession : public SocketHandler
{
    Q_OBJECT

public:
    ClientSession(QTcpSocket* socket);

    // Handlers
    void HandleClientVersion(QByteArray datas);
    void HandleAuthentification(QByteArray datas);

    // Requests
    void RequestCoachCreation();

public slots:
    void OnDisconnection();

signals:
    void Disconnected();

private:
    virtual void ProcessPacket(quint16 opcode, QByteArray packet);

    AccountInfos m_infos;
};

#endif // AUTHSOCKET_H
