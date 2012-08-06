PROJECTDIR = $${PWD}
include("../common.pri")

TARGET = qamus
QT += gui
TEMPLATE = app
HEADERS = *.h
SOURCES = *.cpp
INCLUDEPATH += ../lib
LIBS += -L../lib/$${DESTDIR} -lqamus

CODECFORTR = UTF-8
TRANSLATIONS += ../translations/*.ts
