#-------------------------------------------------
#
# Project created by QtCreator 2018-12-07T09:41:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cypher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    algorithmes.cpp \
    affichagetext.cpp

HEADERS  += mainwindow.h \
    algorithmes.h \
    affichagetext.h

FORMS    += mainwindow.ui \
    affichagetext.ui

OTHER_FILES += \
    README.txt
