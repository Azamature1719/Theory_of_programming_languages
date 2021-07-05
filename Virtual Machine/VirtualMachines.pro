TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        arithmeticsAddress.cpp \
        arithmeticsAddressNum.cpp \
        arithmeticsFloat.cpp \
        arithmeticsInteger.cpp \
        command.cpp \
        comparison.cpp \
        cpu.cpp \
        io.cpp \
        jump.cpp \
        main.cpp \
        memory.cpp \
        movements.cpp

HEADERS += \
    arithmeticsAddress.h \
    arithmeticsAddressNum.h \
    arithmeticsFloat.h \
    arithmeticsInteger.h \
    command.h \
    comparison.h \
    cpu.h \
    io.h \
    jump.h \
    memory.h \
    movements.h \
    structures.h
