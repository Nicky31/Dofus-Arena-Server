#include "SocketHandler.h"

SocketHandler::SocketHandler(QTcpSocket *socket)
{
    m_socket = socket;
    m_socket->setParent(this);
    m_packetSize = 0;

    QObject::connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead()));
}

QString SocketHandler::GetIp() const
{
    return m_socket->peerAddress().toString();
}

QTcpSocket* SocketHandler::GetSocket() const
{
    return m_socket;
}

void SocketHandler::OnRead()
{
    QDataStream stream(m_socket);

    while(m_socket->bytesAvailable())
    {
        if(m_packetSize == 0)
        {
            if(m_socket->bytesAvailable() < (qint64)sizeof(short))
                return;

            stream >> m_packetSize;
            m_packetSize -= 2; // On enlève les 2 octets de la taille
        }

        if(m_socket->bytesAvailable() < m_packetSize) // Toutes les données ne sont pas encore disponibles
            return;

        quint16 opcode;
        quint8 unk;
        stream >> unk; // 3eme octet du header des packets de DA qui semble etre inutile
        stream >> opcode;

        ProcessPacket(opcode, m_socket->read(m_packetSize - 3));

        m_packetSize = 0;
    }
}


void SocketHandler::SendPacket(DAPacket &packet) const
{
    m_socket->write(packet.GetDatas());
    Log::Instance()->Write(DETAIL_LOG, "Envoi du paquet : " + QString::number(packet.GetOpcode()) +
                                       ", Taille : " + QString::number(packet.GetDatas().length()) +
                                       ", Client : " + GetIp());
}
