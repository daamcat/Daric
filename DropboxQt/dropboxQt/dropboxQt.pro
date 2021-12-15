# Ref: https://github.com/osoftteam/dropboxQt

QT       += network xml
QT       -= gui
CONFIG += staticlib
CONFIG -= flat
TEMPLATE = lib

# The name of this .pro file must be the same as the name of its containing folder. Otherwise qmake doesn't find it!!!
# Specifies the name of the target file. Contains the base name of the project file by default:
TARGET = dropboxQt


API_MODULES = async auth files properties sharing team team_common team_policies users endpoint
# When using DropboxQt library as static in another Qt project, For defining SRC_DIR, we must use $$PWD.
# Ref: https://stackoverflow.com/questions/21482248/qmake-referencing-a-library-using-relative-paths/21524024
# SRC_DIR = $$PWD/../src
SRC_DIR = $$PWD/../src
API_DIR = $${SRC_DIR}/dropbox

message(Inside dropboxQt.pro: $$PWD)
for(m, API_MODULES){
       d = $${API_DIR}/$${m}
       exists($${d}){
           message($${d})
           HEADERS += $${d}/*.h
           SOURCES += $${d}/*.cpp
       }
}

HEADERS += $${API_DIR}/*.h
SOURCES += $${API_DIR}/*.cpp

################################################################
# autotest generation (internal profiling usage)               #
#                                                              #
# HEADERS += $${API_DIR}/AUTOTEST/*.h                          #
# SOURCES += $${API_DIR}/AUTOTEST/*.cpp                        #
# DEFINES += API_QT_AUTOTEST                                   #
################################################################

INCLUDEPATH += $${SRC_DIR}



