#include "OpcodesMgr.h"

OpcodesList OpcodesMgr::opcodes;

void OpcodesMgr::Add(OpcodeID opcode, OpcodeHandlerPtr ptr, quint8 requirements)
{
    OpcodeHandler handler;
    handler.ptr = ptr;
    handler.requirements = requirements;

    opcodes.insert(opcode, handler);
}

void OpcodesMgr::Load()
{
    Add(CMSG_CLIENT_VERSION, &ClientSession::HandleClientVersion,    NO_ACCOUNT_NEEDED);
    Add(CMSG_AUTHENTICATION, &ClientSession::HandleAuthentification, NO_ACCOUNT_NEEDED);
    Add(CMSG_COACH_CREATION, &ClientSession::HandleCoachCreation,    ACCOUNT_NEEDED | NO_COACH_NEEDED);
}

OpcodeHandlerPtr OpcodesMgr::GetHandler(short id)
{
    return opcodes.value((OpcodeID)id).ptr;
}

quint8 OpcodesMgr::GetRequirements(short id)
{
    return opcodes.value((OpcodeID)id).requirements;
}

bool OpcodesMgr::Exists(short id)
{
    return opcodes.contains((OpcodeID)id);
}
