QT       += core network
QT       -= gui

#SRC_DIR = $$PWD/../DropboxQt/src
#ENDPOINT_DIR = $${SRC_DIR}/endpoint
#STONE_GENERATED_DIR = $${SRC_DIR}/stone

#INCLUDEPATH += $${STONE_GENERATED_DIR} $${SRC_DIR}
# Adds dropboxQt project path to the header file include lookup path (so we can use the headers in code)
INCLUDEPATH += $$PWD/../src

message(Inside dropbox.pri pwd: $$PWD)


##############################################################
#  specify path to the dropboxQt lib, on windows it can be   #
#   ../../dropboxQt/debug/ on unix - shadow build path       #
##############################################################
message(Inside dropbox.pri out_pwd: $$OUT_PWD)


PRE_TARGETDEPS += $${OUT_PWD}/../DropboxQt/dropboxQt/release/libdropboxQt.a
LIBS += -L$$OUT_PWD/../DropboxQt/dropboxQt/release/ -ldropboxQt

