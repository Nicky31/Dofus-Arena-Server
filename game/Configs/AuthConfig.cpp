#include "AuthConfig.h"

AuthConfig* AuthConfig::instance = 0;

AuthConfig* AuthConfig::Instance()
{
    if(instance == 0)
    {
        instance = new AuthConfig();
    }

    return instance;
}

AuthConfig::AuthConfig() : Config()
{
    m_filePath = "configs/AuthConfig.conf";
    m_format = QSettings::IniFormat;
    LoadConfig();
}

void AuthConfig::Close()
{
    delete instance;
}

void AuthConfig::GenerateDefaultSettings(QSettings &settings)
{
#define SET(index, defaultVal) \
    settings.setValue(index, defaultVal);

    SET("CLIENT_VERSION", "2.6");
    SET("SERVER_IP",      "127.0.0.1");
    SET("SERVER_PORT",    "5555");

#undef SET
}
