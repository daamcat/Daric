#-------------------------------------------------
#
# Project created by QtCreator 2021-01-07T16:08:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts sql

TARGET = DaricLib
TEMPLATE = lib
CONFIG += staticlib

DEFINES +=SOURCE_DIR=\\\"$$PWD\\\"


include(../Config/Config.pri)


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        AddRecord.cpp \
        Chart.cpp \
        Configuration.cpp \
        CreateSqliteDatabase.cpp \
        DeleteRecord.cpp \
        EditRecord.cpp \
        GraphicsScene.cpp \
        GraphicsView.cpp \
        IdentityProxyModel.cpp \
        MySqlTableModel2.cpp \
        NewRecordWidget.cpp \
        PushButtonRecordEdit.cpp \
        TableManager.cpp \
        TableModel.cpp \
        TableView.cpp \
        TableWidget.cpp \
        UserActivityController.cpp \
        MainWindow.cpp \
        mysqltablemodel.cpp \
        databasemanager.cpp \
        DaricLib.cpp


HEADERS += \
        AddRecord.h \
        Chart.h \
        Configuration.h \
        CreateSqliteDatabase.h \
        DeleteRecord.h \
        EditRecord.h \
        GraphicsScene.h \
        GraphicsView.h \
        IdentityProxyModel.h \
        MainWindow.h \
        MySqlTableModel2.h \
        NewRecordWidget.h \
        PushButtonRecordEdit.h \
        TableManager.h \
        TableModel.h \
        TableView.h \
        TableWidget.h \
        UserActivityController.h \
        mysqltablemodel.h \
        databasemanager.h \
        DaricLib.h


FORMS += \
        MainWindow.ui \
        NewRecordWidget.ui


unix {
    target.path = /usr/lib
    INSTALLS += target
}
