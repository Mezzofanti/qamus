#include <QApplication>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>

#include "common.h"
#include "log.h"
#include "mainwindow.h"
#include "options.h"

extern QtMsgType LogLevel;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Options* options = new Options(argc, argv);
    if (options == nullptr)
    {
        qFatal("insufficient memory");
        return ERROR_MEMORY;
    }

    switch(options->getLogLevel())
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
    default:
        LogLevel = QtDebugMsg;
        break;
    }
    qInstallMsgHandler(Logger);

    QTranslator translator;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QString filename = QString("gui_%1").arg(QLocale::system().name()).toLower();
    if (translator.load(filename, ":/translations") == false)
    {
        qWarning() << "unable to load translation: " << filename;
    }

    a.installTranslator(&translator);
    MainWindow w(options);
    w.show();
    int result = a.exec();

    delete options;
    return result;
}
