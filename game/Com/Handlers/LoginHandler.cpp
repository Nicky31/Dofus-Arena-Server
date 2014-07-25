#include "game/Com/Session/ClientSession.h"

// préférons les define étant donné que ces valeurs n'ont pas besoin d'être utilisé autre part
#define SUCCESS        0
#define BAD_LOGINS     2
#define ALREADY_LOGGED 3
#define CURRENTLY_SAVE 4
#define CLOSED_BETA    127

void ClientSession::HandleClientVersion(QByteArray datas)
{
    quint8 version = ExtractNum<quint8>(datas);
    quint16 subVersion = ExtractNum<quint16>(datas);
    quint8 buildRevSize = ExtractNum<quint8>(datas); // Pas besoin puisque la revision occupe les derniers octets

    QStringList versionList = AuthConfig::Instance()->GetQString("CLIENT_VERSION").split(".");
    if(versionList.at(0) != QString::number(version) || versionList.at(1) != QString::number(subVersion))
    {
        DAPacket badVersion(SMSG_INVALID_CLIENT_VERSION);
        badVersion << (quint8)2 << (quint16)6;
        SendPacket(badVersion);
    }
}

void ClientSession::HandleAuthentification(QByteArray datas)
{
    QString account, password;
    quint8 size = ExtractNum<quint8>(datas);

    account = datas.left(size);
    datas.remove(0, size);
    size = ExtractNum<quint8>(datas);
    password = datas.left(size);

    m_account = DAOFactory::GetAccountDAO()->Get(account, password);

    if(m_account == 0)
    {
        SendPacket(DAPacket(SMSG_AUTHENTIFICATION_RESULT) << (quint8)BAD_LOGINS);
        return;
    }
    if(m_account->online)
    {
        SendPacket(DAPacket(SMSG_AUTHENTIFICATION_RESULT) << (quint8)ALREADY_LOGGED);
        delete m_account;
        m_account = 0;
        return;
    }

    SendPacket(DAPacket(SMSG_AUTHENTIFICATION_RESULT) << (quint8)SUCCESS);
    m_account->online = true;
    DAOFactory::GetAccountDAO()->Update(m_account);

    if(!LoadCoach())
        RequestCoachCreation();
    else
        EnterInstance();
}

void ClientSession::SendQueuePosition()
{
    DAPacket packet(SMSG_QUEUE_POS);
    SendPacket(packet);
}
