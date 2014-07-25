#include "game/Com/Session/ClientSession.h"

#define SUCCESS       0
#define INVALID_NAME  11
#define UNDEFINED_ERR 10

Coach* ClientSession::GetCoach() const
{
    return m_account->coach;
}

bool ClientSession::LoadCoach()
{
    if(m_account->coach_id == -1)
        return false;

    m_account->coach = DAOFactory::GetCoachDAO()->Get(m_account->coach_id);
    if(m_account->coach == 0) // Suppresion du coach depuis la db sans corriger l'account
    {
        Log::Instance()->Write(WARNING_LOG, "EnterInstance: Coach id " + QString::number(m_account->coach_id) + " du compte " + m_account->username + " inexistant.");
        m_account->coach_id = -1;
        return false;
    }

    return true;
}

void ClientSession::RequestCoachCreation()
{
    DAPacket request(SMSG_COACH_CREATION_REQUEST);
    SendPacket(request);

    SendQueuePosition();
}

void ClientSession::HandleCoachCreation(QByteArray datas)
{
    quint8 nameSize, skinColorIndex, hairColorIndex, sex;
    QString name;
    DAPacket result(SMSG_COACH_CREATION_RESULT);

    nameSize = ExtractNum<quint8>(datas);
    name = datas.left(nameSize);

    datas.remove(0, nameSize);

    skinColorIndex = ExtractNum<quint8>(datas);
    hairColorIndex = ExtractNum<quint8>(datas);
    sex = ExtractNum<quint8>(datas);

    if(!name.contains(QRegExp("^[a-zA-Z\-]{3,15}$")) ||
       !DAOFactory::GetCoachDAO()->CheckName(name))
    {
        result << (quint8)INVALID_NAME;
        SendPacket(result);
        return;
    }
    if((skinColorIndex + hairColorIndex) > 30)
    {
        result << (quint8)UNDEFINED_ERR;
        SendPacket(result);
        return;
    }

    Coach* newCoach = new Coach;
    newCoach->name = name;
    newCoach->skinColorIndex = skinColorIndex;
    newCoach->hairColorIndex = hairColorIndex;
    newCoach->sex = sex;
    newCoach->id = DAOFactory::GetCoachDAO()->Create(newCoach);

    if(newCoach->id == -1) // Erreur d'insertion || récupération de l'id impossible
    {
        result << UNDEFINED_ERR;
        delete newCoach;
        SendPacket(result);
        return;
    }

    result << SUCCESS;
    SendPacket(result);

    m_account->coach = newCoach;
    m_account->coach_id = newCoach->id;

    EnterInstance();
}

void ClientSession::SendCoachInformations()
{
    // contains Id&Name/Look/Equipement/CardInventory/LaddersStrength
    DAPacket datas(SMSG_COACH_INFORMATIONS);

    datas << (quint64)m_account->coach->id;
    datas << (quint8)m_account->coach->name.size();
    datas << m_account->coach->name;

    datas << m_account->coach->skinColorIndex;
    datas << m_account->coach->hairColorIndex;
    datas << m_account->coach->sex;

    datas << (quint16)0; // Nbre d'octets sur le stuff : non géré

    datas << (quint16)0; // unserializeLockedSet

    datas << (quint16)0; // Nbre d'octets sur l'inventaire: non géré

    // "ladders strength" :
    datas << (quint8)0; // (quint8)count (boucle)
        //iteration:0
            //(quint8)ladderId
            //(quint16)strength

    SendPacket(datas);
}
