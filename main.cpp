#include "QCoreApplication"
#include "QtCore"
#include "game/World/World.h"

using namespace std;

void exit(int)
{
    World::Close();
    QCoreApplication::exit(0);
}

int main(int argc, char* argv[])
{
    QCoreApplication ap(argc, argv);

    signal(SIGABRT, exit);
    signal(SIGTERM, exit);
    signal(SIGINT, exit);

    World world;
    if(!world.Initialize())
        return false;

    return ap.exec();
}
