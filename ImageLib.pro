TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BMP_Reader.cpp \
        BMP_ReaderRead.cpp \
        BMP_ReaderWrite.cpp \
        Canvas.cpp \
        ImageReader.cpp \
        main.cpp

HEADERS += \
    BMP_Reader.h \
    Canvas.h \
    ImageReader.h
