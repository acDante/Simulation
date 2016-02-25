#include "mainwindow.h"

TimeThread::TimeThread()
{

}

void TimeThread::run()
{
   while(time<setTime)
   {
      time++;
   }

   IsRunnning = false;
}
