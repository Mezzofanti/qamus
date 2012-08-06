PROJECTDIR = $${PWD}
TESTNAME   = test_lib
include("test.pri")

INCLUDEPATH += ../lib
LIBS += -L../release -lqamus
