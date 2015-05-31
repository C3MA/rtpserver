#-------------------------------------------------
#
# Project created by QtCreator 2015-03-08T22:56:49
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = rtp-test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rtpparser.c \
    rtpclient.cpp

HEADERS += \
    rtpclient.h \
    rtp.h \
    rtpparser.h
