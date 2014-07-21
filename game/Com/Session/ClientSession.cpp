#include "ClientSession.h"

ClientSession::ClientSession(QTcpSocket *socket) : SocketHandler(socket)
{
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnection()));
}

void ClientSession::OnDisconnection()
{
    Log::Instance()->Write(DETAIL_LOG, "Deconnexion de " + GetIp()  + ".");
    emit Disconnected();
}

void ClientSession::ProcessPacket(quint16 opcode, QByteArray packet)
{
    Log::Instance()->Write(DETAIL_LOG, "Reception du paquet : " + QString::number(opcode) +
                                       ", Taille : " + QString::number(packet.size()) +
                                       ", Client : " + GetIp());

    if(OpcodesMgr::Exists(opcode))
    {
        (this->*(OpcodesMgr::Get(opcode)))(packet);
    }
    else
        Log::Instance()->Write(WARNING_LOG, "Reception d'un opcode inconnu : " + QString::number(opcode));
}

