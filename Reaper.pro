TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

SOURCES += main.cpp \
    peak.cpp \
    scan.cpp \
    msrun.cpp \
    mzxml_reader.cpp \
    alignment_node.cpp \
    alignment_chain.cpp \
    alignment.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    peak.h \
    scan.h \
    msrun.h \
    mzxml_reader.h \
    alignment_node.h \
    alignment_chain.h \
    alignment.h

QT += core
