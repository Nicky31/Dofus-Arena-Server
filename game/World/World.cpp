#include "World.h"

World::World() : m_server()
{
}

World::~World()
{
    qDeleteAll(m_clients);
    m_clients.clear();

    Log::Instance()->Write(WARNING_LOG, "Fermeture du serveur ...");
    Log::Close();
    AuthConfig::Close();

    delete m_dynDb;
}

void World::Update()
{
    QTcpSocket* newSocket;
    if((newSocket = m_server.GetServer()->nextPendingConnection()) != NULL)
    {
        ClientSession* newClient = new ClientSession(newSocket);
        m_clients.append(newClient);

        Log::Instance()->Write(DETAIL_LOG, "Nouvelle connexion de " + newClient->GetIp());

        QObject::connect(newClient, SIGNAL(Disconnected()), this, SLOT(OnDisconnection()));
    }
}

void World::OnDisconnection()
{
    ClientSession* client = qobject_cast<ClientSession*>(sender());
    assert(client != 0 && "pointeur client nul");

    Log::Instance()->Write(DETAIL_LOG, "Deconnexion de " + client->GetIp()  + ".");

    m_clients.removeAll(client);
    client->deleteLater();
}

bool World::Initialize()
{
    Log::Instance()->SetLogTypeFile(ERROR_LOG, "logs/error_logs.txt");
    Log::Instance()->SetLogTypeFile(WARNING_LOG, "logs/warning_logs.txt");

    if(!AuthConfig::Instance()->IsLoaded())
        return false;

    OpcodesMgr::Load();

    QStringList connectionIds = AuthConfig::Instance()->GetQString("DYN_DB").split(":");
    m_dynDb = new DatabaseConnection(connectionIds.takeFirst(), connectionIds.takeFirst(), connectionIds.takeFirst(), connectionIds.takeFirst(), connectionIds.takeFirst().toInt());
    if(!m_dynDb->Open())
        return false;
    DAOFactory::SetDynDB(m_dynDb);

    if(!m_server.StartOn(AuthConfig::Instance()->GetQString("SERVER_IP"),
                         AuthConfig::Instance()->GetInt("SERVER_PORT")))
        return false;

    m_server.Attach(this);

    return true;
}

