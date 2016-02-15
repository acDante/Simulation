#include "mainwindow.h"
#include<QTime>

#define MAX_PEOPLE_NUMBER 10;
#define DOOR_ENERGY 1;
#define FLOOR_UP_ENERGY 20;
#define FLOOR_DOWN_ENERGY 10;
#define DOOR_TIME 5;
#define FLOOR_TIME 3;

Elevator::Elevator(){
    stop = true;
    isEmpty = true;
    isRunning = false;
    maxPeopleNumber = MAX_PEOPLE_NUMBER;
    peopleNumber = 0;

    //随机生成电梯的初始停靠楼层
    //srand((unsigned)time(0));
    atFloor = rand()%5 + 1;

    doorEnergy = DOOR_ENERGY;
    floorUpEnergy = FLOOR_UP_ENERGY;
    floorDownEnergy = FLOOR_DOWN_ENERGY;
    people = NULL;
    //doorTime = DOOR_TIME;
    //floorTime = FLOOR_TIME;

    //楼层
    floor = new Floor[5];
}

int Elevator::searchMaxTime(){
    int maxTime = 0;
    for(int i = 0;i<5;i++){
        if(maxTime<this->floor[i].searchMaxTime())
            maxTime = this->floor[i].searchMaxTime();
    }
    return maxTime;
}

int Elevator::searchMaxFloor(){
    int maxTime = 0;
    int maxFloor = 0;
    for(int i = 0;i<5;i++){
        if(maxTime<this->floor[i].searchMaxTime())
            maxFloor = i;
    }
    return maxFloor;
}

void Elevator::stay(){
    this->stop = true;
}

void Elevator::run(){
    this->maxFloor = searchMaxFloor();
    this->stop = false;
    if(this->maxFloor<atFloor)
        this->up = false;
    else{
        if(this->maxFloor>atFloor)
            this->up = true;

        //else
          //  this->up = ;
    }
}

