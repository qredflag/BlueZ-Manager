######################################################################
# Automatically generated by qmake (2.01a) vie oct 29 13:25:24 2010
######################################################################

TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qdbus

# Input
HEADERS += \
    bluez/manager.h \
    bluez/adapter.h \
    bluez/device.h \
    bluez/types.h \
    adapterview.h \
    mainwindow.h \
    deviceview.h \
    deviceswindow.h
SOURCES += main.cpp \
    bluez/manager.cpp \
    bluez/adapter.cpp \
    bluez/device.cpp \
    adapterview.cpp \
    mainwindow.cpp \
    deviceview.cpp \
    deviceswindow.cpp

FORMS += \
    adapterview.ui \
    deviceview.ui \
    deviceswindow.ui

# qDBUS_ADAPTORS += bluez/org.bluez.manager.xml \
#    bluez/orb.bluez.adapter.xml
