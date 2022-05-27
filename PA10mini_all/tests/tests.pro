QT = core testlib
TARGET = tst_manzhuk
CONFIG += testcase
CONFIG -= app_bundle

HEADERS += tst_manzhuk.h \
           ../sources/manzhuk/manzhuk.h

SOURCES += tst_manzhuk.cpp \
           ../sources/manzhuk/manzhuk.cpp

INCLUDEPATH += ../sources \
               ../sources/manzhuk
