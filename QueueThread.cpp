#include<mainwindow.h>
void QueueThread::run()
   {
      sum = initialpeopleNum;
      while(IsRunning == true && sum<=100)
      {
       formertime = gettime;
       gaptime = randomNum;

       while(gettime - formertime<gaptime)
       {
        }
       passengerNum = randomNum;
       for(int i = ;i<passengerNum;i++)
       {
           peopleThread.start();
       }

          sum+=passengerNum;
      }

   }
