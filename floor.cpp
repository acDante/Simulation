#include"mainwindow.h"
/*--便于查看floor类声明--
class Floor
{
    friend class Elevator;
    bool hasWaitingPerson;      // 本楼层是否有乘客发出了请求标志（1表示“是”，0表示“否”）-->在add第一项和delete第一项后可能发生变化，通过PeopleNum == 0？ 来判断
    int peopleNum;    // 本楼层当前等待电梯的乘客数 --> 即链表项数
    int longestWaitTime;// 本楼层最长等待时间; --> 即队列头的乘客的等待时间 （一直在变 如何处理）

    Passenger* searchMaxTime(int& max_time);// 寻找本楼层乘客中的最大候梯时间 --》遍历乘客链表 找出最大候梯时间和乘客指针

public slots:
    void AddPerson(Passenger* p);    // 在链队列里加入新乘客p
    Passenger* DeletePerson(Passenger* p); // 将链队列里的乘客p删除，并返回指向被删除乘客的指针

private:
    Floor();
    QLinkedList<Passenger> queue;    // 当前楼层中处于等待电梯状态的乘客的链队列
    QLinkedList<Passenger>::iterator itr;  // 用于遍历乘客链队列的迭代器
};*/

Floor::Floor()
{
    hasWaitingPerson = 0;
    peopleNum = 0;
    longestWaitTime = 0;
    itr = queue.begin();     // 迭代器开始指向链表首
}

Passenger* Floor::searchMaxTime(int& max_time, VTime& t)
{
    if(!hasWaitingPerson)  // 当前楼层没有人在等待
    {
        max_time = 0;
        return NULL;
    }
    itr = queue.begin();
    Passenger* temp;
    max_time = - t.GetCurVTime().secsTo(itr -> requestTime);
    for(itr; itr!=queue.end(); itr++)
    {
        if(- t.GetCurVTime().secsTo(itr -> requestTime) > max_time)
        {
            max_time = - t.GetCurVTime().secsTo(itr -> requestTime);
            temp = &(*itr);
        }
    }
    return temp;
}

void Floor::AddPerson(Passenger* p, VTime &t)  // 在链队列里加入新乘客p
{
    queue.append(*p);                  // append()是在链表尾部加入新项
    if(!hasWaitingPerson)              // 若之前没人在等电梯
        hasWaitingPerson = 1;
    peopleNum++;
    searchMaxTime(longestWaitTime,t);  // 更新最长等待时间
}

void Floor::DeletePerson(Passenger* p, VTime &t)  // 将链队列里的乘客p删除，并返回指向被删除乘客的指针
{
   /* queue.removeOne(*p);
    peopleNum--;
    if(peopleNum == 0)
    {
        hasWaitingPerson = 0;
    }
    searchMaxTime(longestWaitTime,t);  // 更新最长等待时间*/
}
