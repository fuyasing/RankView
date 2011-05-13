#-------------------------------------------------
#
# Project created by QtCreator 2011-05-12T21:38:46
#
#-------------------------------------------------

QT       += core gui

TARGET = RankView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        conodegraphicsitem.cpp \
        colinegraphicsitem.cpp \
    graphics.cpp \
    nodedata.cpp \
    plotwizard.cpp

HEADERS  += mainwindow.h \
         conodegraphicsitem.h \
         colinegraphicsitem.h \
    graphics.h \
    nodedata.h \
    plotwizard.h

FORMS    += mainwindow.ui \
    plotwizard.ui