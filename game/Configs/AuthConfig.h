#ifndef AUTHCONFIG_H
#define AUTHCONFIG_H

#include <QtCore>
#include "core/Configurations/Config.h"

class AuthConfig : public Config
{

public:
    static AuthConfig* Instance();
    static void Close();

private:
    AuthConfig();
    virtual void GenerateDefaultSettings(QSettings &settings);

    static AuthConfig* instance;

};

#endif // AUTHCONFIG_H
