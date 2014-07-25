#ifndef OPCODESMGR_H
#define OPCODESMGR_H

#include <QtCore>
#include "game/Com/Session/ClientSession.h"

class ClientSession;
typedef void(ClientSession::*OpcodeHandlerPtr)(QByteArray);

enum OpcodeID
{
    // Client messages
    CMSG_CLIENT_VERSION = 7,
    CMSG_AUTHENTICATION = 1025,
    CMSG_COACH_CREATION = 2049,

    // Server messages
    SMSG_INVALID_CLIENT_VERSION = 8,
    SMSG_AUTHENTIFICATION_RESULT = 1024,
    SMSG_RECONNECTION_TICKET = 2,
    SMSG_COACH_CREATION_REQUEST = 2048,
    SMSG_COACH_CREATION_RESULT = 2050,
    SMSG_COACH_INFORMATIONS = 2052,
    SMSG_ENTER_INSTANCE = 4600,
    SMSG_QUEUE_POS = 8192 // Non géré

};

enum OpcodeRequirement
{
    NONE              = 0,
    ACCOUNT_NEEDED    = 1,
    NO_ACCOUNT_NEEDED = 2,
    COACH_NEEDED      = 4,
    NO_COACH_NEEDED   = 8
};

struct OpcodeHandler
{
    OpcodeHandlerPtr ptr;
    quint8 requirements;
};

typedef QMap<OpcodeID, OpcodeHandler> OpcodesList;

class OpcodesMgr
{
public:
    static void Add(OpcodeID opcode, OpcodeHandlerPtr ptr, quint8 requirements);
    static void Load();
    static OpcodeHandlerPtr GetHandler(short id);
    static quint8 GetRequirements(short id);
    static bool Exists(short id);

private:
    static OpcodesList opcodes;
};

#endif // OPCODESMGR_H
