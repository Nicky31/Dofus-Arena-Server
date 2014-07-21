#include "World.h"

// Permet de ne pas re-appeller Close() dans le cas où Close est appellé avant le destructeur :
bool World::is_running = false;

World::World() : m_server()
{
}

World::~World()
{
    World::Close();
}

void World::Close()
{
    if(is_running)
    {
        Log::Instance()->Write(WARNING_LOG, "Fermeture du serveur ...");
        Log::Close();
        AuthConfig::Close();
        is_running = false;
    }
}

bool World::Initialize()
{
    Log::Instance()->SetLogTypeFile(ERROR_LOG, "logs/error_logs.txt");
    Log::Instance()->SetLogTypeFile(WARNING_LOG, "logs/warning_logs.txt");

    if(!AuthConfig::Instance()->IsLoaded())
        return false;

    OpcodesMgr::Load();

    if(!m_server.StartOn(AuthConfig::Instance()->GetQString("SERVER_IP"),
                         AuthConfig::Instance()->GetInt("SERVER_PORT")))
        return false;

    is_running = true;
    return true;
}
