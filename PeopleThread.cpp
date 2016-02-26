#include "mainwindow.h"

PeopleThread::PeopleThread()
{
    people.toFloor = randomNum();
    people.arrivaltime = gettime();
    people.staytime = 0;
    //wait();

}

void run()
{

    while(IsRunning == true)
    {
          if(gettime() - people.arrivaltime >= people.staytime)//如果乘客在楼层的停留时间到了
          {
              people.signal();//乘客发信号
          }

          waitbegintime = gettime();

          wait();//进行等待，乘客线程被挂起，等待电梯线程的唤醒

          if(gettime - waitbegintime <=longestWaitTime)
         {
              people.getIn();
              wait();
              people.getOut();
              people.arrivaltime = gettime();
              people.staytime = randomNum();//生成随机等待时间
         }

         else
         {
         people.arrivaltime = gettime();
             people.staytime = randomNum();
         }
   }
}
