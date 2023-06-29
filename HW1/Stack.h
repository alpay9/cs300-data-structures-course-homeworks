#pragma once
#include <iostream>
//Alpay Nacar

template <typename T>
struct ListNode
{
    T data;
    ListNode* next;
    ListNode(const T& data, ListNode* next = nullptr) : data(data), next(next) {}
};

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();

    void push(const T& x);
    void pop();
    ListNode<T>*& top();
    void makeEmpty();
private:
    ListNode<T>* head;
};

#include "stack.cpp"