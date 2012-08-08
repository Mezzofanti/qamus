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

    QString text = QDateTime::currentDateTime().toString(Qt::ISODate) + " ";
    if (type == QtDebugMsg)
    {
        text += QString("debug");
    }
    else if (type == QtWarningMsg)
    {
        text += QString("warn.");
    }
    else if (type == QtCriticalMsg)
    {
        text += QString("crit.");
    }
    else if (type == QtFatalMsg)
    {
        text += QString("fatal");
    }
    else
    {
        return;
    }

    text += ": ";
    text += msg;

    if (LogToFile && !LogFile.isEmpty())
    {
        QFile outFile(LogFile);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << text << endl;
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
