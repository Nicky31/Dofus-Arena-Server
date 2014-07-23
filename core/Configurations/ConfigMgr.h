#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <QtCore>
#include "Config.h"

class ConfigMgr
{

public:
    static ConfigMgr* Instance();
    bool LoadConfig(QString const& filename);

private:
    static ConfigMgr* instance;
    ConfigMgr() {};

};

#endif // CONFIGMGR_H
