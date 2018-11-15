TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Driver.cpp \
    Word.cpp \
    parser.cpp \
    tinyxml2.cpp \
    cParser.cpp \
    HtmlParser.cpp

HEADERS += \
    Driver.h \
    avltree.h \
    Word.h \
    parser.h \
    tinyxml2.h \
    cParser.h \
    HtmlParser.hpp





