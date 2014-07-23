#include "ClientSession.h"

ClientSession::ClientSession(QTcpSocket *socket) : SocketHandler(socket)
{
    m_account = 0;
    m_authentified = false;
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnection()));
}

ClientSession::~ClientSession()
{
    // Sauvegardes ...
    if(m_authentified)
    {
        m_account->online = false;
        DAOFactory::GetAccountDAO()->Update(m_account);
    }

    // Account n'est pas forcément instancié, comme dans le cas d'un échec de connexion :
    if(m_account != 0)
        delete m_account;
}

void ClientSession::OnDisconnection()
{
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

