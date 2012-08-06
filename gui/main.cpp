#include <QApplication>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>

#include "mainwindow.h"
#include "options.h"
#include "common.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

    QString filename = QString("gui_%1").arg(QLocale::system().name()).toLower();
    if (translator.load(filename, ":/translations") == false)
    {
        qDebug() << "[" << __FILE__ << "] unable to load translation: " << filename;
    }

    Options* options = new Options(argc, argv);
    if (options == nullptr)
    {
        return ERROR_MEMORY;
    }

    a.installTranslator(&translator);
    MainWindow w(options);
    w.show();
    int result = a.exec();

    delete options;
    return result;
}
