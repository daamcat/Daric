TEMPLATE = app
QT += core
QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

EP_BASE = $$OUT_PWD/3rdParty
include($$PWD/GTest.pri)

TARGET = FreeTesting
SOURCES += main.cpp
DEPENDPATH += $$EP_BASE/Install/gtest/include
INCLUDEPATH += $$EP_BASE/Install/gtest/include
LIBS += -L$$EP_BASE/Install/gtest/lib/ -lgtest -lgmock