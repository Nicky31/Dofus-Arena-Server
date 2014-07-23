#ifndef LOG_H
#define LOG_H

#include <QtCore>
#include "iostream"

using namespace std;

enum LogType
{
    DETAIL_LOG,
    WARNING_LOG,
    ERROR_LOG
};

class Log
{

public:
    ~Log();
    static Log* Instance();
    static void Close();

    bool SetLogTypeFile(LogType logType, QString const& filePath);
    void Write(LogType logType, QString const& msg);

private:
    Log();
    QString LogFileFormat(QString const& log);
    QString LogConsoleFormat(LogType logType, QString const& log);

    static Log* instance;
    QMap<LogType, QFile*> m_logFiles;

};

#endif // LOG_H
