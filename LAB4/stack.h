#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20;

template<typename dataType>
class stack
{
    private:
        dataType data[MAX_SIZE];
        int size;
    public:
        stack();
        void push(dataType val);
        void pop();
        dataType top();
        bool empty() const;
};

template<typename dataType>
stack<dataType>::stack()
{
    size = 0;
}
template<typename dataType>
void stack<dataType>::push(dataType val)
{
    if(size == MAX_SIZE)
    {
        throw overflow_error("Called push on full stack.");
    }

    data[size] = val;
    size++;
}
template<typename dataType>
void stack<dataType>::pop()
{
    if(empty())
    {
        throw out_of_range("Called pop on empty stack.");
    }

    size--; //shoutout to Laura Huerta for helping me out :-)
}
template<typename dataType>
dataType stack<dataType>::top()
{
    if(empty())
    {
        throw underflow_error("Called top on empty stack.");
    }

    return data[size - 1];
}
template<typename dataType>
bool stack<dataType>::empty() const
{
    if(size == 0)
    {
        return true;
    }

    return false;
}
#endif