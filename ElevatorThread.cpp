#include "mainwindow.h"

Elevator::Elevator()
{
    //实例化楼层数组
    floor = new floor[5];
}

//电梯开门时
void ElevatorThread::openDoor()
{
    //当前时间加上电梯的开门时间
   v_time->pass(elevator.doorTime);

   //唤醒要在本层上或者下电梯乘客
   elevatorArrived.wakeAll();
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
