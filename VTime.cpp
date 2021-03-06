#include "mainwindow.h"
#include <QtCore>
#define rtime_interval 1     // 单位为毫秒
// 当前换算： 现实世界 1ms = 虚拟时间 0.5s
VTime::VTime()
{
    vtime.setHMS(8,0,0);    // 初始时间为上午的8:00
    realtime = new QTimer(this);
    connect(realtime,SIGNAL(timeout()),this,SLOT(pass()));
}

void VTime::start() // 虚拟时间开始流逝
{
    realtime->start(rtime_interval);
}

void VTime::stop()  // 虚拟时间停止
{
    realtime->stop();
}

void VTime::pass(int secs = 1/2 * rtime_interval)  // 虚拟时间流逝的过程
{
    vtime = vtime.addSecs(secs);
}

QTime VTime::GetCurVTime()  // 用时间序列数组获取当前的虚拟时间
{
    return vtime;
}

int VTime::GetCurVHour()    // 获取当前虚拟时间的小时部分
{
    return vtime.hour();
}

int VTime::GetCurVMin()     // 获取当前虚拟时间的分钟部分
{
    return vtime.minute();
}

int VTime::GetTotalVSecs()  // 当前虚拟时间共经过多少秒
{
    return (vtime.hour() - 8) * 3600 + vtime.minute() * 60 + vtime.second();
}

