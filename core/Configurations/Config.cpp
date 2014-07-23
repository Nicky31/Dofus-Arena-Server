#include "Config.h"

Config::Config()
{
}

void Config::LoadConfig()
{
    QSettings settings(m_filePath, m_format);

    // Settings vides = Fichier inexistant ou vide -> On tente de le générer
    if(settings.allKeys().count() == 0)
    {
        if(settings.isWritable())
        {
            GenerateDefaultSettings(settings);
            settings.sync();
            Log::Instance()->Write(WARNING_LOG, "Le fichier de configuration " + m_filePath + " a ete genere automatiquement. Certains parametres pourraient necessiter d'etre reajuster.");
            return LoadConfig();
        }

        Log::Instance()->Write(ERROR_LOG, "Chargement du fichier de configuration " + m_filePath + " impossible : inexistant et impossible a generer.");
        return;
    }

    QStringList keys = settings.allKeys();
    QStringList::const_iterator i;
    for(i = keys.constBegin(); i != keys.constEnd(); ++i)
    {
        m_settings.insert(*i, settings.value(*i));
    }
}

bool Config::IsLoaded() const
{
    return !m_settings.isEmpty();
}

QVariant Config::GetValue(const QString &key) const
{
    if(m_settings.contains(key))
        return m_settings.value(key);
    else
    {
        Log::Instance()->Write(ERROR_LOG, m_filePath  + " : Demande de l'index '" + key + "' inexistant.'");
        return QVariant();
        //TODO: Error ....
    }
}

QString Config::GetQString(const QString &key) const
{
    return GetValue(key).toString();
}

bool Config::GetBool(const QString &key) const
{
    return GetQString(key) == "1" || GetQString(key).toLower() == "true";
}

int Config::GetInt(const QString &key) const
{
    return GetValue(key).toInt();
}
