#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TimeThread timeThread;  //时钟线程
    ElevatorThread elevatorThread; // 电梯线程
    PeopleThread*  peopleThread = new PeopleThread[MaxPeopleNum];//乘客线程数组

    return a.exec();
}
