#ifndef OPCODESMGR_H
#define OPCODESMGR_H

#include <QtCore>
#include "game/Com/Session/ClientSession.h"

class ClientSession;

enum OpcodeID
{
    // Client messages
    CMSG_CLIENT_VERSION = 7,
    CMSG_AUTHENTICATION = 1025,

    // Server messages
    SMSG_INVALID_CLIENT_VERSION = 8,
    SMSG_AUTHENTIFICATION_RESULT = 1024,
    SMSG_COACH_CREATION_REQUEST = 2048,
    SMSG_COACH_CREATION_RESULT = 2050,
    SMSG_COACH_INFORMATIONS = 2052,
    SMSG_ENTER_INSTANCE = 4600

};

typedef void(ClientSession::*OpcodeHandlerPtr)(QByteArray);
typedef QMap<OpcodeID, OpcodeHandlerPtr> OpcodesList;

class OpcodesMgr
{
public:
    static void Load();
    static OpcodeHandlerPtr Get(short id);
    static bool Exists(short id);

private:
    static OpcodesList opcodes;
};

#endif // OPCODESMGR_H
