#include "mainwindow.h"
/*  --便于查看passenger类声明--
    int request; // 是否发出了请求标志（1表示“发出上行请求”，0表示“未发出请求”，-1表示“下行请求”）
    int srcFloor;// 乘客当前所在楼层
    int desFloor;// 乘客所要前往楼层（随机生成，当随机的前往楼层是1时，认为乘客已经离开大楼）
    int status; // 乘客在当前楼层的状态 （"1"表示停留在该楼层工作,"2"表示等待电梯,"3"表示在电梯里）
    static int inOutTime;// 乘客上下电梯的时间
    QTime requestTime;   // 乘客发出乘梯请求的时刻
    QTime getinTime;     // 乘客乘上电梯的时刻
    QTime arrivalTime;   // 乘客到达所前往楼层的时刻
    int stayTime;        // 乘客所前往楼层的停留时间（随机生成）
    int tolerationTime;  // 乘客最大忍受时限

    Passenger();            //乘客的构造函数
    void getIn(VTime& t);           //进入电梯
    void getOut(Elevator& lift, VTime& t);  //走出电梯
    void sendSignal(VTime& t);//发出信号
    void stay(VTime& t);    //在楼层停留

*/
Passenger::Passenger()
{
    request = NONE; // 初始无请求
    srcFloor = 1;    // 假设新乘客总是从第一层到来
    status = STAY;  // 假设初始为停留状态
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));// 随机生成乘客在该楼层的起始停留时间（产生3~6 min的随机数）
    stayTime = 1/10 *MIN_STAY_TIME + qrand() % (1/10 *MAX_STAY_TIME - 1/10 *MIN_STAY_TIME + 1);
    // 待补充？
    // 在哪里给inOutTime赋值？ inOutTime应与乘客队列长度有关。
}

void Passenger::sendSignal(VTime* t)//发出乘梯请求
{
    stayTime = 0;         // 初始化停留时间
    do{
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        desFloor = qrand() % 5 + 1; // 随机产生乘客的目标楼层（得到与当前所处的楼层不同的一个随机数）
    }while(desFloor == srcFloor);
    if (desFloor > srcFloor)
        request = UP;      // 置上行标志
    else
        request = DOWN;     // 置下行标志
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));  // 随机生成乘客的最长忍耐时限 0.8*（30~60min）的随机数
    tolerationTime =0.8 *(MIN_WAIT_TIME + qrand() % (MAX_WAIT_TIME - MIN_WAIT_TIME + 1));
    requestTime = t->GetCurVTime();
    status = WAIT;
    emit come(this);     // 向楼层发出“到来”信号  -> 楼层接到该信号后应将该乘客加入等待链表。
}

void Passenger::getIn(VTime* t)  //进入电梯
{
    request = NONE;
    status = INLIFT;
    getinTime = t->GetCurVTime();
    tolerationTime = 0;          // 初始化乘客最大忍耐时限
}

void Passenger::getOut(VTime* t) // 走出电梯
{
    arrivalTime = t->GetCurVTime();
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    stayTime = MIN_STAY_TIME + qrand() % (MAX_STAY_TIME - MIN_STAY_TIME + 1); // 随机生成乘客在该楼层的停留时间
    srcFloor = desFloor;
    desFloor = 0;                // 初始化目标楼层(0表示无意义的楼层)
}
// --------stay()函数待补充 ---------
void Passenger::stay(VTime* t)  // 在楼层停留
{
    status = STAY;
    // 待补充
    // 乘客线程睡眠，经过一个stayTime后被时间线程唤醒。
}
// --------stay()函数待补充 ---------
void Passenger::UpdateWaitTime(VTime* t) // 不断更新当前乘客的等待时间，如果等待时间超出最大忍耐时限会发出leave()信号
{
    QTime current = t->GetCurVTime();
    int waitTime = - current.secsTo(requestTime);
    if(waitTime >= tolerationTime)
        emit leave(this);  // 向楼层发出“离开”信号  -> 楼层接到该信号后应将该乘客从等待链表中删去。
}
