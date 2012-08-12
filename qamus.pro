CONFIG  += debug_and_release warn_on ordered
TEMPLATE = subdirs
SUBDIRS  = lib gui
app.depends = lib

OTHER_FILES += CHANGELOG INSTALL README