PROJECTDIR = $${PWD}
include("../common.pri")

CONFIG += qtestlib release
CONFIG -= debug
DESTDIR = 
TRANSLATIONS =
RESOURCES = 
SOURCES += $${TESTNAME}.cpp 

TARGET = $${TESTNAME}

target.path   = $${PROJECTDIR}
sources.files = $${PROJECTDIR}/ *.pro
sources.path  = $${PROJECTDIR}/

MOC_DIR     = $${PROJECTDIR}/moc
OBJECTS_DIR = $${PROJECTDIR}/obj

INSTALLS += target sources
