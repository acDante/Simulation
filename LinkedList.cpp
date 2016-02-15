#include "LinkedList.h"

template<class T>
LinkedList<T>::~LinkedList<T>()
{
    Node<T>* temp;
        while (head)
        {
            temp = head ->link;
            delete head;
            head = temp;
        }
}

template<class T>
bool LinkedList<T>::IsFull()const
{
    try
        {
            Node<T>* temp = new Node<T>;
            delete temp;
            return false;
        }
        catch(Invalid)
        {
            return true;
        }
}

template<class T>
int LinkedList<T>::GetLength()const
{
    if(IsEmpty())
            return 0;
        Node<T>* temp = head;
        int length = 0;
        while (head)
        {
            length++;
            temp = temp -> link;
        }
        return length;
}

template<class T>
void LinkedList<T>::Destroy()
{
    Node<T>* temp;
        while (head)
        {
            temp = head ->link;
            delete head;
            head = temp;
        }
}

template<class T>
T LinkedList<T>::GetHead()const
{
    return *head;
}

template<class T>
LinkedList<T>& LinkedList<T>::Insert(const T& x)
{
    if(IsEmpty())
    {
        head = new Node<T>(x);
        tail = head;
        return this;
    }
    if(IsFull())
        throw Invalid();
    Node<T> *temp = new Node<T>(x);
    tail -> link = temp;
    tail = temp;
    return this;
}

template<class T>
LinkedList<T>& LinkedList<T>::Delete(int k, T& x)  //删除第k个结点
{
    if(!IsEmpty())
    {
        int cur = 1;
        Node<T> *temp = head;
        Node<T> *ptemp;
        while(cur < k && temp)
        {
            ptemp = temp;
            temp = temp -> link;
            cur ++;
        }
        if(cur < k)
            throw Invalid();
        ptemp -> link = temp -> link;
        delete temp;
        return this;
    }
    return this;
}

//删掉所有值为key的链表结点并在参数中返回删掉的总节点数
