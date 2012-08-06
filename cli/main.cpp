#include <QCoreApplication>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>

#include "options.h"
#include "common.h"

int main(int argc, char* argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

    Options* options = new Options(argc, argv);
    if (options == nullptr)
    {
        return ERROR_MEMORY;
    }

    delete options;
}
