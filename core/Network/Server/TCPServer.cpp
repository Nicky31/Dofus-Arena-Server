#include "TCPServer.h"

TCPServer::TCPServer()
{
    m_server = new QTcpServer();
}

TCPServer::~TCPServer()
{
    delete m_server;
}

QTcpServer* TCPServer::GetServer() const
{
    return m_server;
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
    Notify();
}
