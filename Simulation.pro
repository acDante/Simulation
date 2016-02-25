#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T12:15:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Frame.cpp \
    Door.cpp \
    attrdlg.cpp \
    elevator.cpp \
    passenger.cpp \
    floor.cpp \
    VTime.cpp \
    ElevatorThread.cpp \
    PeopleThread.cpp \
    TimeThread.cpp

HEADERS  += mainwindow.h \
    F:/Hundred Project/Simulation/LinkedList.h \
    F:/Hundred Project/Simulation/LinkedList.h \
    F:/Hundred Project/Simulation/LinkedList.h \
    attrdlg.h

FORMS    += mainwindow.ui \
    attrdlg.ui
