#include "mainwindow.h"

PeopleThread::PeopleThread()
{
    //people.desFloor = randomNum();
    people.arrivalTime = v_time->GetCurVTime();
    people.staytime = 0;
    //wait();
}

void PeopleThread::run()
{
    while(IsRunning == true)
    {
          QTime current = v_time->GetCurVTime();
          if(- current.secsTo(people.arrivalTime) >= people.stayTime)//如果乘客在楼层的停留时间到了
          {
              people.sendSignal(v_time);//乘客发信号
              wait();//进行等待，乘客线程被挂起，等待电梯线程的唤醒
          }
          current = v_time->GetCurVTime();
          if(- current.secsTo(people.requestTime)<= people.tolerationTime)
          {
              people.getIn();
              wait();
              people.getOut();
          }
          else
          {
              people.arrivalTime = v_time->GetCurVTime();
              qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
              people.stayTime = MIN_STAY_TIME + qrand() % (MAX_STAY_TIME - MIN_STAY_TIME + 1); // 重新生成乘客在该楼层的停留时间
          }
    }
}
