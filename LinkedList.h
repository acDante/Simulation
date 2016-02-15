#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<iostream>
#include<fstream>
using namespace std;
class Invalid: public exception
{
public:
    Invalid(){ cout<< "非法访问！" ; }
};

template <class T>
class LinkedList;         //类声明；

template <class T>
class Node
{
    friend class LinkedList<T>;
public:
    T data;
    Node<T> *link;
};

template <class T>
class LinkedList
{
    Node<T> *head,*tail;
public:
    LinkedList() { head = tail = NULL; }
    ~LinkedList();
    bool IsEmpty()const { return head == NULL; }     // 判断链表是否为空
    bool IsFull()const;                              // 判断链表是否已满
    int GetLength()const;                            // 获得链表长度
    void Destroy();                                  // 清空链表
    T GetHead()const;                                // 获取链表头的值
    LinkedList<T>& Insert(const T& x);              // 在链表尾部插入新节点
    LinkedList<T>& Delete(int k, T& x);             // 删除第k个结点
};

#endif // LINKEDLIST_H
