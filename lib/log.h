#ifndef LOG_H
#define LOG_H

#include "common.h"

#include <iostream>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

QtMsgType LogLevel;
QString   LogFile;
bool      LogToFile = false;
bool      LogToConsole  = true;


static void Logger(QtMsgType type, const char *msg)
{
    if (LogLevel > type)
    {
        return;
    }

    QString text;
    if (type == QtDebugMsg)
    {
        text = QString("DEBUG ");
    }
    else if (type == QtWarningMsg)
    {
        text = QString("WARN  ");
    }
    else if (type == QtCriticalMsg)
    {
        text = QString("CRIT  ");
    }
    else if (type == QtFatalMsg)
    {
        text = QString("FATAL ");
    }
    else
    {
        return;
    }

    text = QDateTime::currentDateTime().toString(Qt::ISODate) + " " + text + msg;

    if (LogToFile && !LogFile.isEmpty())
    {
        QFile outFile(LogFile);
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            QTextStream ts(&outFile);
            ts << text << endl;
        }
        else
        {
            LogToFile = false;
            qCritical() << "unable to write to log file" << LogFile;
        }
    }
    if (LogToConsole)
    {
        if (type == QtDebugMsg || type == QtWarningMsg)
        {
            std::cout << text.toStdString() << std::endl;
        }
        else
        {
            std::cerr << text.toStdString() << std::endl;
        }
    }
}

#endif // LOG_H
