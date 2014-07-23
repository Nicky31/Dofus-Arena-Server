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
    signal(SIGHUP, exit); // Fermeture de la fenêtre, checker sous windows

    World world;
    if(!world.Initialize())
        return false;
    return ap.exec();
}
