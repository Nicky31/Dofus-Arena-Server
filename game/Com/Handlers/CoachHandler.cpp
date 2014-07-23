#include "game/Com/Session/ClientSession.h"

#define SUCCESS       0
#define INVALID_NAME  11
#define UNDEFINED_ERR 10

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
    if(skinColorIndex > 15 || hairColorIndex > 15)
    {
        result << (quint8)UNDEFINED_ERR;
        SendPacket(result);
        return;
    }

    Coach* newCoach = new Coach;
    newCoach->name = name;
    newCoach->skinColorIndex = skinColorIndex;
    newCoach->hairColorIndex = hairColorIndex;
    newCoach->sex = (unsigned char)sex;
    newCoach->id = DAOFactory::GetCoachDAO()->Create(newCoach);

    if(newCoach->id != -1)
    {
        result << SUCCESS;
        m_account->coach = newCoach;
        m_account->coach_id = newCoach->id;
    }
    else
    {
        result << UNDEFINED_ERR;
        delete newCoach;
    }

    SendPacket(result);
}
