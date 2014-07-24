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

    DAPacket authResult(SMSG_AUTHENTIFICATION_RESULT);
    if(m_account != 0)
        if(m_account->online)
        {
            authResult << (quint8)ALREADY_LOGGED;
            m_authentified = false;
        }
        else
        {
            authResult << (quint8)SUCCESS;
            m_account->online = m_authentified = true;
            DAOFactory::GetAccountDAO()->Update(m_account);
        }
    else
    {
        authResult << (quint8)BAD_LOGINS;
        m_authentified = false;
    }

    SendPacket(authResult);

    AUTHENTIFIED_REGION

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
