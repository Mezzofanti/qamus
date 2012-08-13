#include <QApplication>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>

#include "common.h"
#include "log.h"
#include "mainwindow.h"
#include "options.h"

extern QtMsgType LogLevel;
extern QString   LogFile;
extern bool      LogToFile;
extern bool      LogToConsole;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qInstallMsgHandler(Logger);

#ifdef _WIN32
    Options* options = nullptr;
    int logLevel = -1;
    LogToConsole = true;
    LogToFile = false;
    LogFile = nullptr;
#else
    Options* options = new Options(argc, argv);
    if (options == nullptr)
    {
        qFatal("insufficient memory");
        return ERROR_MEMORY;
    }
    int logLevel = options->getLogLevel();
    LogToConsole = options->getLogToConsole();
    LogToFile = options->getLogToFile();
    LogFile = options->getLogFilename();
#endif // _WIN32

    switch(logLevel)
    {
    case 0:
        LogLevel = QtFatalMsg;
        break;
    case 1:
        LogLevel = QtCriticalMsg;
        break;
    case 2:
        LogLevel = QtWarningMsg;
        break;
    case 3:
        LogLevel = QtDebugMsg;
        break;
    default:
#ifdef QT_DEBUG
        LogLevel = QtDebugMsg;
#else
        LogLevel = QtCriticalMsg;
#endif
        break;
    }
    qDebug() << "logging at level" << LogLevel;

    QTranslator translator;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QString filename = QString("gui_%1").arg(QLocale::system().name()).toLower();
    if (translator.load(filename, ":/translations") == false)
    {
        qCritical() << "unable to load translations for locale" << QLocale::system().name();
    }

    a.installTranslator(&translator);
    MainWindow w(options);
    w.show();
    int result = a.exec();

    delete options;
    return result;
}
