#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T21:54:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Space-program
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TwoVector.cpp \
    Body.cpp \
    CelestialSystem.cpp \
    SpaceWidget.cpp

HEADERS  += MainWindow.h \
    TwoVector.h \
    Body.h \
    CelestialSystem.h \
    gslroutine.h \
    SpaceWidget.h

FORMS    += MainWindow.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -lgsl -lgslcblas -lm

DISTFILES +=

RESOURCES +=
