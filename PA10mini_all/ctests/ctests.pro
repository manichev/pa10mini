TARGET = ctest_manzhuk

CONFIG -= app_bundle

DEFINES += MANZHUK_TEST

HEADERS += ctest_manzhuk.h \
           ../pa10mini/manzhuk/manzhuk.h

SOURCES += ctest_manzhuk.cpp \
           ../pa10mini/manzhuk/manzhuk.cpp

INCLUDEPATH += ../pa10mini \
               ../pa10mini/manzhuk
