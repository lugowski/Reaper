TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    peak.cpp \
    scan.cpp \
    msrun.cpp \
    base64.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    peak.h \
    scan.h \
    msrun.h \
    base64.h

