QT       += core gui quick qml network positioning location


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QMAKE_CXX = g++-4.9

QMAKE_CXXFLAGS += -std=c++11

QMAKE_CXXFLAGS += -Wall


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    computationthread.cpp \
    model.cpp \
    Recuit.cpp \
    RecuitDeterministe.cpp \
    RecuitStochastique.cpp \
    SAA.cpp \
    Scenario.cpp \
    Station.cpp \
    Stochastique.cpp \
    VLS.cpp \
    Algorithme.cpp \
    Localisation.cpp \
    Probleme.cpp

HEADERS += \
    mainwindow.h \
    computationthread.h \
    model.h \
    json.hpp \
    Recuit.h \
    RecuitDeterministe.h \
    RecuitStochastique.h \
    SAA.h \
    Scenario.h \
    Station.h \
    Stochastique.h \
    VLS.h \
    Algorithme.h \
    Localisation.h \
    Probleme.h

RESOURCES += \
    places_map.qrc
