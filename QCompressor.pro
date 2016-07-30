#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T12:01:55
#
#-------------------------------------------------

QT       += core

CONFIG += console

TARGET = QCompressor
TEMPLATE = app

INCLUDEPATH += ../

SOURCES += main.cpp\        
    ../qt_enhance/compressor/file_compressor.cpp \
    ../qt_enhance/compressor/folder_compressor.cpp

HEADERS  += ../qt_enhance/compressor/file_compressor.hpp \
    ../qt_enhance/compressor/folder_compressor.hpp
