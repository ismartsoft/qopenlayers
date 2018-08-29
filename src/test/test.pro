
QT += core gui widgets

TARGET = $$qtLibraryTarget(test)
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000

CONFIG += c++11

DESTDIR = $$PWD/../../bin

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CentralWidget.h \
    MainWindow.h \
    StyledFrame.h

SOURCES += \
    CentralWidget.cpp \
    main.cpp \
    MainWindow.cpp \
    StyledFrame.cpp

## library qol

DEFINES += \
    QOL_LIB

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bin -lqol
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bin -lqold
else:unix: LIBS += -L$$PWD/../../bin -lqol

INCLUDEPATH += $$PWD/../qol
DEPENDPATH += $$PWD/../qol
