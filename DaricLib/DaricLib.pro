#-------------------------------------------------
#
# Project created by QtCreator 2021-01-07T16:08:21
#
#-------------------------------------------------
# The name of this .pro file must be the same as the name of its containing folder. Otherwise qmake doesn't find it!!!
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts sql

############# DropboxQt #####################
INCLUDEPATH += $$PWD/../DropboxQt/src
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DropboxQt/dropboxQt/release/ -ldropboxQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DropboxQt/dropboxQt/debug/ -ldropboxQt
############# DropboxQt #####################


# To include C++17 features
CONFIG += c++17

# TARGET Specifies the name of the target file. Contains the base name of the project file by default:
TARGET = DaricLib
TEMPLATE = lib
#CONFIG += staticlib

DEFINES +=SOURCE_DIR=\\\"$$PWD\\\"

include(../Config/Config.pri)

#include(../DropboxQt/dropboxQt/dropbox-common.pri)

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
        ChangeTable.cpp \
        Chart.cpp \
        ComboBoxCostEntry.cpp \
        Configuration.cpp \
        CostEntryForm.cpp \
        CreateSqliteDatabase.cpp \
        DatabaseManager.cpp \
        DateEdit.cpp \
        DeleteRecord.cpp \
        EditRecord.cpp \
        GraphicsScene.cpp \
        GraphicsView.cpp \
        IdentityProxyModel.cpp \
        LabelDropBox.cpp \
        MySqlTableModel2.cpp \
        PushButtonRecordEdit.cpp \
        SortFilterProxyModel.cpp \
        TableEditForm.cpp \
        TableModel.cpp \
        TableView.cpp \
        TableWidget.cpp \
        TimeRangeForm.cpp \
        UserActivityController.cpp \
        MainWindow.cpp \
        WalletFilterDialog.cpp \
        WidgetDropBox.cpp \
        mysqltablemodel.cpp \
        DaricLib.cpp


HEADERS += \
        AddRecord.h \
        ChangeTable.h \
        Chart.h \
        ComboBoxCostEntry.h \
        Configuration.h \
        CostEntryForm.h \
        CreateSqliteDatabase.h \
        DatabaseManager.h \
        DateEdit.h \
        DeleteRecord.h \
        EditRecord.h \
        GraphicsScene.h \
        GraphicsView.h \
        IdentityProxyModel.h \
        LabelDropBox.h \
        MainWindow.h \
        MySqlTableModel2.h \
        PushButtonRecordEdit.h \
        SortFilterProxyModel.h \
        TableEditForm.h \
        TableModel.h \
        TableView.h \
        TableWidget.h \
        TimeRangeForm.h \
        UserActivityController.h \
        WalletFilterDialog.h \
        WidgetDropBox.h \
        mysqltablemodel.h \
        DaricLib.h


FORMS += \
        CostEntryForm.ui \
        MainWindow.ui \
        TableEditForm.ui \
        TimeRangeForm.ui \
        WalletFilterDialog.ui \
        WidgetDropBoxForm.ui


unix {
    target.path = /usr/lib
    INSTALLS += target
}




