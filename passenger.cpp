#include "mainwindow.h"

Passenger::Passenger()
{
    inLift = 0;
    signal = 0;
    atFloor = 1; // 假设新乘客总是从第一层到来
    toFloor = 0; // "0"表示无意义的楼层
    static QTime inOutTime;//乘客上下电梯的时间
    QTime requestTime;  //乘客发出乘梯请求的时刻
    QTime arrivalTime;  //乘客到达所前往楼层的时刻
    QTime stayTime;//乘客所前往楼层的停留时间（随机生成）
    QTime tolerationTime;//乘客最大忍受时限
}

void Passenger::sendSignal()//发出乘梯请求
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    toFloor; = qrand() % 5 + 1;  // 随机产生乘客的目标楼层
    signal = 1;

}

void Passenger::getIn()  //进入电梯
{
}

void Passenger::getOut() //走出电梯
{
}

void Passenger::stay()  //在楼层停留
{
    // 乘客线程睡眠，经过一个stayTime后被时间线程唤醒。
}
