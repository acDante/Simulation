#include "mainwindow.h"

VTime::VTime()
{
    hour = 8;       // 起始时间为早上8:00
    minute = 0;
    second = 0;
    realtime = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(pass()));
}

void VTime::start() // 虚拟时间开始流逝
{
    realtime->start(1);
}

void VTime::stop()  // 虚拟时间停止
{
    realtime->stop();
}

void VTime::pass()  // 虚拟时间流逝的过程
{
    second += 10;
    if (second == 60)
    {
        second = second % 60;
        minute ++;
        if (minute == 60)
        {
            minute = minute % 60;
            hour ++;
        }
    }
}

void VTime::GetCurVTime(int* time_sequence) // 获取当前的虚拟时间
{
    time_sequence[0] = hour;
    time_sequence[1] = minute;
    time_sequence[2] = second;
}

int VTime::GetCurVHour()    // 获取当前虚拟时间的小时部分
{
    return hour;
}

int VTime::GetCurVMin()     // 获取当前虚拟时间的分钟部分
{
    return minute;
}

int VTime::GetTotalVSecs()  // 当前虚拟时间共经过多少秒
{
    return (hour - 8) * 3600 + minute * 60 + second;
}

