PROJECTDIR = $${PWD}
include("../common.pri")

TARGET = qamus
QT += gui
TEMPLATE = app
HEADERS = *.h
SOURCES = *.cpp
FORMS = *.ui

INCLUDEPATH += ../lib
DEPENDPATH *= $${INCLUDEPATH}
LIBS += -L$${DESTDIR} -lqamus
PRE_TARGETDEPS += $${DESTDIR}/libqamus.a

CODECFORTR = UTF-8
TRANSLATIONS += ../translations/*.ts