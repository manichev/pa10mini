QT = core testlib
TARGET = tst_manzhuk
CONFIG += testcase
CONFIG -= app_bundle

HEADERS += tst_manzhuk.h \
           ../pa10mini/manzhuk/manzhuk.h

SOURCES += tst_manzhuk.cpp \
           ../pa10mini/manzhuk/manzhuk.cpp

INCLUDEPATH += ../pa10mini \
               ../pa10mini/manzhuk
