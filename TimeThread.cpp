#include "mainwindow.h"

TimeThread::TimeThread()
{

}

void TimeThread::run()
{
   QTime setTime(18,0,0);
   while(v_time->GetCurVTime() < setTime)
   {
      v_time->pass();
   }
   IsRunnning = false;
}
