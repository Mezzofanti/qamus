PROJECTDIR = $${PWD}
include("../common.pri")

TARGET = qamus
TEMPLATE = app
HEADERS = *.h
SOURCES = *.cpp
INCLUDEPATH += ../lib
LIBS += -L../lib/$${DESTDIR} -lqamus
