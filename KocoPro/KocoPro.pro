#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T16:33:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KocoPro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview_mainmap.cpp \
    graphicsview_smallmap.cpp \
    slider_viewsize.cpp \
    dataandalgorithm.cpp \
    codebuilder.cpp \
    exchangeboard.cpp

HEADERS  += mainwindow.h \
    graphicsview_mainmap.h \
    graphicsview_smallmap.h \
    slider_viewsize.h \
    dataandalgorithm.h \
    codebuilder.h \
    exchangeboard.h

FORMS    += mainwindow.ui \
    exchangeboard.ui

OTHER_FILES +=
