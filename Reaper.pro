TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

SOURCES += main.cpp \
    peak.cpp \
    scan.cpp \
    msrun.cpp \
    base64.cpp \
    mzxml_reader.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    peak.h \
    scan.h \
    msrun.h \
    base64.h \
    mzxml_reader.h

QT += core
