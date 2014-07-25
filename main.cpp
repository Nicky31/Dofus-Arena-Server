#include "QCoreApplication"
#include "QtCore"
#include "game/World/World.h"

using namespace std;

void exit(int s)
{
    QCoreApplication::exit(0);
}

int main(int argc, char* argv[])
{
    QCoreApplication ap(argc, argv);

    signal(SIGTERM, exit);
    signal(SIGINT, exit); // ctrl + c
#ifdef Q_OS_UNIX
    signal(SIGHUP, exit); // Fermeture de la fenêtre
#elif defined(Q_OS_WIN)
    signal(SIGBREAK, exit);
#endif

    World world;
    if(!world.Initialize())
        return false;
    return ap.exec();
}
