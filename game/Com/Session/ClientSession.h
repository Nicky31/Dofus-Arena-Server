#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include "core/Network/Server/SocketHandler.h"
#include "game/Com/Opcodes/OpcodesMgr.h"
#include "game/Configs/Configs.h"
#include "core/Utils/Common.h"
#include "game/DAO/DAOFactory.h"
#include "game/World/Managers/Account/AccountMgr.h"

using namespace std;

class ClientSession : public SocketHandler
{
    Q_OBJECT

public:
    ~ClientSession();
    ClientSession(QTcpSocket* socket);

    // Handlers
    void HandleClientVersion(QByteArray datas);
    void HandleAuthentification(QByteArray datas);
    void HandleCoachCreation(QByteArray datas);

    // Requests
    void RequestCoachCreation();
    void SendQueuePosition(); // Non géré

public slots:
    void OnDisconnection();

signals:
    void Disconnected();

private:
    virtual void ProcessPacket(quint16 opcode, QByteArray packet);

    bool m_authentified;
    Account* m_account;
};

#endif // AUTHSOCKET_H
