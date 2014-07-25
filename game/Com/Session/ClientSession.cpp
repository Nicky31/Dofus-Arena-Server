#include "ClientSession.h"

ClientSession::ClientSession(QTcpSocket *socket) : SocketHandler(socket)
{
    m_account = 0;
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnection()));
}

ClientSession::~ClientSession()
{
    // Sauvegardes ...
    if(m_account != 0)
    {
        m_account->online = false;
        DAOFactory::GetAccountDAO()->Update(m_account);

        delete m_account;
    }
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
        if(Require(OpcodesMgr::GetRequirements(opcode)))
            (this->*(OpcodesMgr::GetHandler(opcode)))(packet);
        else
        {
            Log::Instance()->Write(WARNING_LOG,
                                   "Reception de l'opcode " + QString::number(opcode) +
                                   " sans que le client " + GetIp() + " remplisse les conditions necessaires (" + QString::number(OpcodesMgr::GetRequirements(opcode)) + ").");
            m_socket->abort();
            return;
        }
    }
    else
        Log::Instance()->Write(WARNING_LOG, "Reception d'un opcode inconnu : " + QString::number(opcode));
}

bool ClientSession::Require(quint8 requirement) const
{
    if(!requirement)
        return true;

    if((requirement & ACCOUNT_NEEDED) && m_account == 0)
        return false;

    if((requirement & NO_ACCOUNT_NEEDED) && m_account != 0)
        return false;

    if((requirement & COACH_NEEDED) && m_account->coach == 0)
        return false;

    if((requirement & NO_COACH_NEEDED) && m_account->coach != 0)
        return false;

    return true;
}
