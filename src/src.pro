
QT += core gui widgets

TARGET = test1
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x06000

CONFIG += c++11

DESTDIR = $$PWD/bin

include($$PWD/src/src.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

## libraries

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# library jwt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -ljwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -ljwtd

# library icdcomm

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -licdcomm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -licdcommd

# library icdcore

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -licdcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -licdcored

# library icdparser

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -licdparser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -licdparserd

# library icdworker

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -licdworker
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -licdworkerd
