#ifndef WORLD_H
#define WORLD_H

#include "core/Network/Server/TCPServer.h"
#include "game/Configs/Configs.h"
#include "game/DAO/DAOFactory.h"
#include <cassert>
#include <csignal>
#include <QtCore>

class World : public QObject, public Observer
{
    Q_OBJECT

public:
    World();
    ~World();
    bool Initialize();
    // Notification du TCPServer(Nouvelle connexion) :
    virtual void Update();

public slots:
    void OnDisconnection();

private:
    TCPServer m_server;
    DatabaseConnection* m_dynDb;

    QList<ClientSession*> m_clients;
};

#endif // WORLD_H
