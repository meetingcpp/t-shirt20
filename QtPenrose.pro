#-------------------------------------------------
#
# Project created by QtCreator 2017-10-09T10:56:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg

TARGET = QtPenrose
TEMPLATE = app

CONFIG += c++14
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    CertifiedLibraryLogoCode.cpp \
        main.cpp \
        mainwindow.cpp \
    penrosecanvas.cpp \
    pixelgrouprunner.cpp \
    penrosetiling.cpp \
    penroseshape.cpp \
    pixelgroup.cpp \
    canvas.cpp \
    penroseshapegroup.cpp \
    rasterizedshape.cpp \
    stepwidget.cpp \
    svgexportwidget.cpp

HEADERS += \
        mainwindow.h \
    penrosecanvas.h \
    pixelgrouprunner.h \
    penrosetiling.h \
    penroseshape.h \
    pixelgroup.h \
    canvas.h \
    penroseshapegroup.h \
    rasterizedshape.h \
    shapegroup.h \
    stepwidget.h \
    svgexportwidget.h

FORMS += \
        mainwindow.ui \
    stepwidget.ui \
    svgexportwidget.ui
