#-------------------------------------------------
#
# Project created by QtCreator 2020-11-06T21:03:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts sql


TARGET = Daric
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Adds the DaricLib project path to the header file include lookup path
INCLUDEPATH += $$PWD/../DaricLib

include(../Config/Config.pri)

CONFIG += c++11

SOURCES += main.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# Adds the HelloQt2Lib.lib to the linker
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DaricLib/release/ -lDaricLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DaricLib/debug/ -lDaricLib


