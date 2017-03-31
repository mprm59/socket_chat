#-------------------------------------------------
#
# Project created by QtCreator 2015-05-21T20:23:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerPart
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    server.h

FORMS    += mainwindow.ui

RESOURCES += \
    avatars.qrc

RC_FILE += myapp.rc
DISTFILES += \
    myapp.rc \
    server.ico
