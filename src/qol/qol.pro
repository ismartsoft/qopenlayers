
QT += core gui widgets webchannel websockets webenginewidgets

TEMPLATE = lib
TARGET = $$qtLibraryTarget(qol)

DEFINES += \
    QOL_LIB \
    QOL_BUILD

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000

CONFIG += c++11

DESTDIR = $$PWD/../../bin

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    qol_global.h \
    qol_inc.h \
    QOLView.h

SOURCES += \
    qol_global.cpp \
    QOLView.cpp

RESOURCES += \
    resource/resource.qrc
