#ifndef CONFIG_H
#define CONFIG_H

#include <QtCore>
#include "core/Logs/Log.h"
#include "iostream"

using namespace std;

class Config
{

public:
    bool IsLoaded() const;

    // Accesseurs
    QVariant GetValue(QString const& key) const;
    QString GetQString(QString const& key) const;
    bool GetBool(QString const& key) const;
    int GetInt(QString const& key) const;

protected:
    QString m_filePath;
    QSettings::Format m_format;
    QMap<QString, QVariant> m_settings;

    Config();
    void LoadConfig();
    virtual void GenerateDefaultSettings(QSettings &settings) = 0;

};

#endif // CONFIG_H
