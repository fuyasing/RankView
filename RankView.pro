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
        rankviewdialog.cpp\
        nodedata.cpp \
        plotwizard.cpp \
    tipgraphicsitem.cpp

HEADERS  += mainwindow.h \
         conodegraphicsitem.h \
         colinegraphicsitem.h \
        graphics.h \
        rankviewdialog.h\
        nodedata.h \
        plotwizard.h \
    tipgraphicsitem.h

FORMS    += mainwindow.ui \
        plotwizard.ui

RESOURCES += \
    rankImage.qrc
