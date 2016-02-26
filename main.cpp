#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

<<<<<<< HEAD
=======
    //TimeThread timeThread;  //时钟线程
    //ElevatorThread elevatorThread; // 电梯线程
    //PeopleThread*  peopleThread = new PeopleThread[MAX_PEOPLE_NUM];//乘客线程数组

>>>>>>> refs/remotes/origin/test
    return a.exec();
}
