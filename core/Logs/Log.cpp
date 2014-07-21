#include "Log.h"

Log* Log::instance = 0;

Log* Log::Instance()
{
    if(instance == 0)
    {
        instance = new Log();
    }

    return instance;
}

Log::Log()
{
}

Log::~Log()
{
    qDeleteAll(m_logFiles);
    m_logFiles.clear();
}

void Log::Close()
{
    delete instance;
}

bool Log::SetLogTypeFile(LogType logType, const QString &filePath)
{
    QFile* file = new QFile(filePath);
    if(!file->open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        cout << "ERROR > Logs > Impossible d'ouvrir le fichier " << filePath.toLatin1().data() << " en ecriture." << endl;
        delete file;
        return false;
    }

    m_logFiles.insert(logType, file);
    return true;
}

void Log::Write(LogType logType, const QString &msg)
{
    cout << LogConsoleFormat(logType, msg).toLatin1().data() << endl;

    if(m_logFiles.contains(logType))
    {
        QFile* file = m_logFiles.value(logType);
        file->write(LogFileFormat(msg).toLatin1() + "\n");
        file->flush();
    }
}

QString Log::LogFileFormat(const QString &log)
{
    return QDateTime::currentDateTime().toString("[d/M/yyyy h:m:s] > ") + log;
}

QString Log::LogConsoleFormat(LogType logType, const QString &log)
{
    QString logTypeString;
    switch(logType)
    {
        case WARNING_LOG:
            logTypeString = "[ Warning ] > ";
            break;
        case ERROR_LOG:
            logTypeString = "[ ERROR ] > ";
            break;
        default:
        case DETAIL_LOG:
            logTypeString = "> ";
            break;
    }

    return logTypeString + log;
}
