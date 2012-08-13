CONFIG += debug_and_release
QT      += core xml
QT      -= gui

CONFIG(debug, debug|release) {
    BUILD = debug
} else {
    BUILD = release
    DEFINES = QT_FATAL_WARNING QT_NO_DEBUG_OUTPUT
}

DESTDIR     = ../$${BUILD}
MOC_DIR     = $${PROJECTDIR}/$${DESTDIR}/moc
OBJECTS_DIR = $${PROJECTDIR}/$${DESTDIR}/obj
RCC_DIR     = $${PROJECTDIR}/$${DESTDIR}/rcc
UI_DIR      = $${PROJECTDIR}/$${DESTDIR}/ui

CODECFORTR = UTF-8
RESOURCES += $${IN_PWD}/resources/*.qrc

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS         += -std=c++0x

# if ICU has not been disabled explicitly
!CONFIG(disable-icu):{
    ICU_LIBS += $$system(icu-config --ldflags-libsonly 2>/dev/null)
        !isEmpty(ICU_LIBS) {
                !build_pass:message("Adding support for the ICU library")
                DEFINES += ENABLE_ICU
                LIBS += $${ICU_LIBS}
        } else {
                !build_pass:message("ICU libraries not found")
        }
} else {
        !build_pass:message("ICU support disabled")
}

# if tre has not been disabled explicitly
!CONFIG(disable-tre):{
        TRE_LIBS += $$system(if pkg-config --atleast-version=0.8 tre ; then pkg-config --libs tre 2>/dev/null ; fi)
        !isEmpty(TRE_LIBS) {
                !build_pass:message("Adding support for the tre library")
                DEFINES += ENABLE_TRE
                LIBS += $${TRE_LIBS}
        } else {
                !build_pass:message("tre library >= 0.8 not found")
        }
} else {
        !build_pass:message("tre support disabled")
}
