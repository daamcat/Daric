#-------------------------------------------------
#
# Project created by QtCreator 2020-11-06T21:03:22
#
#-------------------------------------------------

# The name of this .pro file must be the same as the name of its containing folder. Otherwise qmake doesn't find it!!!

QT       += core network gui

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

include($$PWD/../Config/Config.pri)


CONFIG += c++11

SOURCES += main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# Adds the DaricLibLib.lib to the linker:
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DaricLib/release/ -lDaricLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DaricLib/debug/ -lDaricLib

###################### Copy test folder to build directory ##################################
# Ref: https://evileg.com/en/post/476/

PWD_PATH = $$PWD/../Config
DESTDIR_PATH = $$OUT_PWD/../Config

win32 {
  PWD_PATH ~= s,/,\\,g
  DESTDIR_PATH ~= s,/,\\,g
}
unix {

}

# Before assembling the installers, you must copy the files from the project's output folder along with all the DLLs to the data folder that belongs to the package you are building.
copydata.commands = $(COPY_DIR) $$PWD_PATH $$DESTDIR_PATH
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
# We set a custom build target, in which we first perform file compiling and then the rest, which follows the QMake script
QMAKE_EXTRA_TARGETS += first copydata
###################### Copy test folder to build directory ##################################
