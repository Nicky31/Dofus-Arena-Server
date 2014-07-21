#include "TCPServer.h"

TCPServer::TCPServer()
{
    m_server = new QTcpServer(this);
}

TCPServer::~TCPServer()
{
    qDeleteAll(m_clients);
    m_clients.clear();
}

bool TCPServer::StartOn(QString ip, quint16 port)
{
    if(!m_server->listen(QHostAddress(ip), port))
    {
        Log::Instance()->Write(ERROR_LOG, "Lancement du serveur impossible : " + m_server->errorString());
        return false;
    }

    QObject::connect(m_server, SIGNAL(newConnection()), this, SLOT(OnConnect()));

    Log::Instance()->Write(DETAIL_LOG, "Lancement du serveur sur le port " + QString::number(port) + "\nEn attente de connexions ...");
    return true;
}

void TCPServer::OnConnect()
{
    ClientSession* newClient = new ClientSession(m_server->nextPendingConnection());
    m_clients.append(newClient);

    Log::Instance()->Write(DETAIL_LOG, "Nouvelle connexion de " + newClient->GetIp());

    QObject::connect(newClient, SIGNAL(Disconnected()), this, SLOT(OnDisconnection()));
}

void TCPServer::OnDisconnection()
{
    ClientSession* client = qobject_cast<ClientSession*>(sender());
    assert(client != 0 && "pointeur client nul");

    RemoveSocket(client);
}

void TCPServer::RemoveSocket(ClientSession *socket)
{
    m_clients.removeOne(socket);
    socket->deleteLater();
}
