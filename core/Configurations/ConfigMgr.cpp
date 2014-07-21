#include "ConfigMgr.h"

ConfigMgr* ConfigMgr::instance = 0;

ConfigMgr* ConfigMgr::Instance()
{
    if(instance == NULL)
    {
        instance = new ConfigMgr();
    }

    return instance;
}

bool ConfigMgr::LoadConfig(const QString &filename)
{

}
