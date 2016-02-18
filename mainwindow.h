#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include "LinkedList.h"
#include "attrdlg.h"

#define MAX_PEOPLE_NUM 100 //整个仿真过程中最大的乘梯人数

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

//乘客类
class Passenger

{
    bool inLift;//是否在电梯里（1表示“是”，0表示“否”）
    bool signal;//是否发出了请求标志（1表示“是”，0表示“否”）
    bool up;    //是否上行（1表示“上行”，0表示“下行”）
    int atFloor;//当前所在楼层
    int toFloor;//所要前往楼层（随机生成，当随机的前往楼层是1时，认为乘客已经离开大楼）
    static QTime inOutTime;//乘客上下电梯的时间
    QTime requestTime;//乘客发出乘梯请求的时刻
    QTime arrivalTime;//乘客到达所前往楼层的时刻
    QTime stayTime;//乘客所前往楼层的停留时间（随机生成）
    QTime tolerationTime;//乘客最大忍受时限


    Passenger();//乘客的构造函数
    void getIn();//进入电梯
    void getOut();//走出电梯
    void sendSignal();//发出信号
    void stay();//在楼层停留
};

//******************************************************************************

class Floor
{
    friend class Elevator;
    bool signal;//本楼层是否有乘客发出了请求标志（1表示“是”，0表示“否”）
    int peopleNumber;//本楼层当前人数
    Passenger *people;//指向当前楼层中的乘客链表
    int longestWaitTime;//本楼层最长等待时间;

    static int searchMaxTime();//寻找本楼层乘客中的最大候梯时间
};

//******************************************************************************

//电梯类
class Elevator
{
public:
    int status;   //"1"表示上行，"0"表示停止，"-1"表示i下行
    bool isEmpty;//当前电梯是否为空载
    bool isRunning;//电梯是否处在仿真
    int maxPeopleNumber;//电梯内最多可容纳人数
    int peopleNumber;//当前电梯内人数
    int curFloor;//当前所在楼层
    int nextFloor;//候梯时间最大乘客所在楼层
    double doorEnergy;//电梯开关门的能耗
    double floorUpEnergy;//电梯上行一层的能耗
    double floorDownEnergy;//电梯下行一层的能耗
    LinkedList<LinkedList<Passenger> > *people;//指向在电梯中的乘客链表
    Floor *floor;    //楼层
    QTime doorTime;//开关门的时间
    QTime floorTime;//电梯运行一层的时间


    Elevator();//电梯构造函数
    int searchMaxTime();//寻找所有乘客中的最大候梯时间
    int searchNextFloor();//寻找等待时间最长的乘客的所在楼层
    void stay();//电梯停靠的函数
    void run();//电梯运行的函数
};
//******************************************************************************

//虚拟时钟类
class VTime         // 模拟一天的时间流逝 按照 现实1ms = 虚拟10s 来换算(这个比例暂定)
{
public:
    int hour;       // 按照24小时制
    int minute;
    int second;

    VTime();
    void GetCurVTime(int* time_sequence); // 获取当前虚拟时间
    int GetCurVHour();  // 获取当前虚拟时间的小时部分
    int GetCurVMin();   // 获取当前虚拟时间的分钟部分
    int GetTotalVSecs();// 当前虚拟时间共经过多少秒
    void start();       // 虚拟时间开始流逝
    void stop();        // 虚拟时间停止

public slots:
    void pass();        // 虚拟时间的流逝过程

private:
    QTimer* realtime;
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

    //乘客指针数组
    Passenger** p;
    //电梯
    Elevator *elevator;

private slots:
    void on_StartSimul_clicked();
    void on_Settings_clicked();

private:
    Ui::MainWindow *ui;

};



#endif // MAINWINDOW_H
