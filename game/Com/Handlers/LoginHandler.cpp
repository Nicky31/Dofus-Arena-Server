#include "game/Com/Session/ClientSession.h"

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

    // Premier octet : 0 pour réussite, le reste pour erreurs :
    // 2 = badlogin / 3 = already connected / 4 = sauvegarde en cours / 127 = beta fermée
    DAPacket authResult(SMSG_AUTHENTIFICATION_RESULT);

    if(account == "nomdecompte" && password == "motdepasse")
    {
        authResult << (quint8)0;
        m_infos.account = account;
        m_infos.password = password;
        m_infos.authentified = true;
    }
    else
    {
        authResult << (quint8)2;
        m_infos.authentified = false;
    }

    SendPacket(authResult);
}

void ClientSession::RequestCoachCreation()
{
    DAPacket request(SMSG_COACH_CREATION_REQUEST);
    SendPacket(request);
}
