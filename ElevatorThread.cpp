#include "mainwindow.h"

ElevatorThread::ElevatorThread()
{
 //只要处理Floor[0]的乘客链表就好
}

//电梯开门时  加开门时间 唤醒要在本层上或者下电梯乘客
void ElevatorThread::openDoor()
{

}

void ElevatorThread::run()
{

    while(IsRunning == true)
    {
        //巡检所有楼层
        for(int i = 0; i<MAX_FLOOR;i++)
        {
           if(Floor[i].signal == true && Floor[i].longestWaitTime>MaxlongestWaitTime)
           {
               judge = true;
               MaxlongestWaitTime = Floor[i].longestWaitTime;
               elevator.maxFloor = i;
           }

        }

        while(elevator.atFloor != elevator.maxFloor)
        {
           if(elevator.atFloor<elevator.maxFloor)
           {
               up = true;
               elevator.run();
           }

           if(elevator.atFloor>elevator.maxFloor)
           {
               up = false;
               elevator.run();
           }

        }
        openDoor();
    }

}
