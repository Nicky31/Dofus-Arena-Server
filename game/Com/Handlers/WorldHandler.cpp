#include "game/Com/Session/ClientSession.h"

void ClientSession::EnterInstance()
{
    SendCoachInformations();

    DAPacket packet(SMSG_ENTER_INSTANCE);
    packet << (float)131072; // worldX
    packet << (float)0; // worldY
    packet << (quint16)0; // altitude
    packet << (quint16)0; // instanceID
    packet << (quint8)0; // dynamic
    SendPacket(packet);

    SendQueuePosition();
}
