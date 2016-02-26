#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QMutableLinkedListIterator>
#include <QThread>
#include <QWaitCondition>
#include "LinkedList.h"
#include "attrdlg.h"

#define INITIAL_PEOPLE_NUM 15//初次乘坐电梯的人数
#define MAX_PEOPLE_NUM 100 // 整个仿真过程中最大的乘梯人数
#define MAX_FLOOR   5
// 用于产生每名乘客的最大忍耐时限
#define MIN_WAIT_TIME 300  // 每名乘客的理论最长等待时间（单位为s）
#define MAX_WAIT_TIME 600  // 每名乘客的理论最长等待时间（单位为s）
// 用于产生每名乘客的停留时间
#define MIN_STAY_TIME 1800 // 乘客在某楼层的最短停留时间（单位为s）
#define MAX_STAY_TIME 3600 // 乘客在某楼层的最长停留时间（单位为s）
//后续乘客到达的时间间隔
#define MIN_GAP_TIME 300
#define MAX_GAP_TIME 600
// 乘客在当前楼层的状态
#define STAY 1     // 停留
#define WAIT 2     // 等待电梯
#define INLIFT 3   // 在电梯中
// 乘客发出的请求类型         and 电梯的状态
#define UP 1       // 上行请求 | 上行中
#define NONE 0     // 无请求
#define DOWN -1    // 下行请求 | 下行中

#define STOP 0     // 停止



namespace Ui {
class MainWindow;
}


//电梯的外部框架
class Frame : public QGraphicsItem
{
public :
    QRectF boundingRect() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

//******************************************************************************

//电梯的门
class Door : public QGraphicsItem
{
public :
    int s;
    QRectF boundingRect() const;
    Door(int ss){s = ss;}
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
//******************************************************************************

//虚拟时钟类
class VTime: public QObject        // 模拟一天的时间流逝 按照 现实1ms = 虚拟10s 来换算(这个比例暂定)
{
    Q_OBJECT

public:
    VTime();
    QTime GetCurVTime(); // 获取当前虚拟时间
    int GetCurVHour();   // 获取当前虚拟时间的小时部分
    int GetCurVMin();    // 获取当前虚拟时间的分钟部分
    int GetTotalVSecs(); // 当前虚拟时间共经过多少秒
    void start();        // 虚拟时间开始流逝
    void stop();         // 虚拟时间停止

public slots:
    void pass();         // 虚拟时间的流逝过程

private:
    QTimer* realtime;
    QTime vtime;         // 按照24小时制

};
//******************************************************************************
//乘客类
class Passenger
{
public:
    int request; // 乘客发出请求的类型 （1表示“发出上行请求”，0表示“未发出请求”，-1表示“下行请求”）
    int srcFloor;// 乘客发出乘梯请求时所在的楼层
    int desFloor;// 乘客所要前往楼层（随机生成一个与当前所在楼层不同的数）
    int status;  // 乘客在当前楼层的状态 （"1"表示停留在该楼层工作,"2"表示等待电梯,"3"表示在电梯里）
    //static int inOutTime;// 乘客上下电梯的时间
    QTime requestTime;   // 乘客发出乘梯请求的时刻
    QTime getinTime;     // 乘客乘上电梯的时刻
    QTime arrivalTime;   // 乘客到达所前往楼层的时刻
    int stayTime;        // 乘客所前往楼层的停留时间（随机生成）
    int tolerationTime;  // 乘客最大忍受时限

    Passenger();            // 乘客的构造函数
    void getIn(VTime* t);   // 进入电梯
    void getOut(VTime* t);  // 走出电梯
    void sendSignal(VTime* t);// 发出信号
    void stay(VTime* t);    // 在楼层停留
    void UpdateWaitTime(VTime* t);  //不断更新当前乘客的等待时间，如果等待时间超出最大忍耐时限会发出leave()信号

signals:
    void come(Passenger* p);  // 开始等待电梯
    void leave(Passenger* p); // 超过最大忍耐时限时，乘客会选择离开，向楼层类Floor[srcFLoor]发出leave()信号
                              // 楼层类接到该信号会将该乘客从链表删去
};

//******************************************************************************
//楼层类： 用于管理等待乘客的链队列
class Floor
{
    friend class Elevator;
    bool hasWaitingPerson;      // 本楼层是否有乘客发出了请求标志（1表示“是”，0表示“否”）-->在add第一项和delete第一项后可能发生变化，通过PeopleNum == 0？ 来判断
    int peopleNum;    // 本楼层当前等待电梯的乘客数 --> 即链表项数
    int longestWaitTime;// 本楼层最长等待时间; --> 即队列头的乘客的等待时间 （一直在变 如何处理）

    Passenger* searchMaxTime(int& max_time, VTime *t);// 寻找本楼层乘客中的最大候梯时间 --》遍历乘客链表 找出最大候梯时间和乘客指针

public slots:
    void AddPerson(Passenger* p, VTime *t);    // 在链队列里加入新乘客p
    void DeletePerson(Passenger* p, VTime *t); // 将链队列里的乘客p删除

private:
    Floor();
    QLinkedList<Passenger> queue;    // 当前楼层中处于等待电梯状态的乘客的链队列
    QLinkedList<Passenger>::iterator itr;  // 用于遍历乘客链队列的迭代器
};

//******************************************************************************

//电梯类
class Elevator
{
public:
    int status;          //"1"表示上行，"0"表示停止，"-1"表示下行
    bool isEmpty;        //当前电梯是否为空载
    bool isRunning;      //电梯是否处在仿真
    int maxPeopleNumber; //电梯内最多可容纳人数
    int peopleNumber;    //当前电梯内人数
    int curFloor;        //当前所在楼层
    int nextFloor;       //候梯时间最大乘客所在楼层
    double doorEnergy;   //电梯开关门的能耗
    double floorUpEnergy;//电梯上行一层的能耗
    double floorDownEnergy;//电梯下行一层的能耗
    //Floor *floor;       //楼层
    int doorTime;//开关门的时间
    int floorTime;//电梯运行一层的时间


    Elevator();//电梯构造函数
    int searchMaxTime(int& nextFloor,Floor* floor,VTime& t);//寻找所有乘客中的最大候梯时间,通过nextFloor返回当前等待时间最长的乘客所在的楼层
    void stay();//电梯停靠的函数
    void run(Floor* floor,VTime& t); //电梯运行的函数
    void MoveOneFloor(Floor* floor);  // 描述电梯行驶一层的函数
    int GetCurFloor(); // 获取电梯当前所在楼层

private:
    QLinkedList<QLinkedList<Passenger> > *people;    //指向在电梯中的乘客链表  ? 相同目标楼层的乘客存在同一个链表中， 用链表的数组好还是链表的链表？？
    QLinkedList<QLinkedList<Passenger> >::iterator itr;
};
//******************************************************************************

//电梯线程类
class ElevatorThread : public QThread
{
     Q_OBJECT
public:
    elevator();
    void opendoor();

protected:
     void run();

private:
     Elevator elevator;
     Floor* floor;
     bool judge;//判断巡检后是否有请求


};


//******************************************************************************

//乘客线程类
class PeopleThread : public QThread
{
     Q_OBJECT
public:
     PeopleThread();

protected:
     void run();

private:
     Passenger people;
};

//******************************************************************************

//后续乘客到达线程类
class QueueThread : public QThread
{
    Q_OBJECT

protected:
    void run();

private:
    int sum;
    QTime formertime;
    int gaptime;
    int passengerNum;
};

//******************************************************************************

//时间线程类
class TimeThread : public QThread
{
     Q_OBJECT
public:
     TimeThread();

protected:
     void run();

private:
     int time;
};

//******************************************************************************

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class elevator;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene *scene;
    QGraphicsScene *scene_1;
    QGraphicsScene *scene_2;
    QGraphicsScene *scene_3;
    QGraphicsScene *scene_4;
    QGraphicsScene *scene_5;


    Frame *f;
    Door *d1;
    Door *d2;
    Door *d3;
    Door *d4;
    Door *d5;
    AttrDlg *attrdlg;

private slots:
    void on_StartSimul_clicked();
    void on_Settings_clicked();

private:
    Ui::MainWindow *ui;

};

//  乘客指针数组
Passenger** p;
//  电梯
Elevator* elevator;
VTime* v_time;

//  判断仿真程序是否运行的标志
bool IsRunning;

//  电梯到达的条件
QWaitCondition elevatorArrived;

#endif // MAINWINDOW_H
