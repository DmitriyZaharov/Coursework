#-------------------------------------------------
#
# Project created by QtCreator 2019-03-27T12:29:28
# QT       += core gui
#-------------------------------------------------


QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UFO_Rescue_spaceship
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ufo.cpp \
    ufo_people.cpp \
    ufo_killer.cpp \
    menuclass.cpp

HEADERS  += mainwindow.h \
    ufo.h \
    ufo_people.h \
    ufo_killer.h \
    menuclass.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource/resource.qrc

OTHER_FILES +=

DISTFILES +=
