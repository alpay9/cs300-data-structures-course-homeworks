#pragma once
#include <iostream>
#include "stack.h"
//Alpay Nacar

template <typename T>
Stack<T>::Stack() : head(nullptr) {}

template <typename T>
Stack<T>::~Stack()
{
    makeEmpty();
}

template <typename T>
void Stack<T>::push(const T& dt)
{
    head = new ListNode<T>(dt, head);
}

template <typename T>
void Stack<T>::pop()
{
    //check for nullptr
    ListNode<T>* temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
ListNode<T>*& Stack<T>::top()
{
    return head;
}

template <typename T>
void Stack<T>::makeEmpty() {
    while (head) {
        pop();
    }
}



