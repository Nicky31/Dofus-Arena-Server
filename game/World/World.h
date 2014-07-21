#ifndef WORLD_H
#define WORLD_H

#include "core/Network/Server/TCPServer.h"
#include "game/Configs/Configs.h"
#include <cassert>
#include <csignal>
#include <QtCore>

class World : public QObject
{
    Q_OBJECT

public:
    World();
    ~World();
    static void Close();

    bool Initialize();

private:
    static bool is_running;
    TCPServer m_server;

};

#endif // WORLD_H
