TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    parser.cpp \
    mystack.cpp \
    myqueue.cpp

HEADERS += \
    parser.h \
    mystack.h \
    myqueue.h
