#include "OpcodesMgr.h"

OpcodesList OpcodesMgr::opcodes;

void OpcodesMgr::Load()
{
    opcodes.insert(CMSG_CLIENT_VERSION, &ClientSession::HandleClientVersion);
    opcodes.insert(CMSG_AUTHENTICATION, &ClientSession::HandleAuthentification);
}

OpcodeHandlerPtr OpcodesMgr::Get(short id)
{
    return opcodes.value((OpcodeID)id);
}

bool OpcodesMgr::Exists(short id)
{
    return opcodes.contains((OpcodeID)id);
}
