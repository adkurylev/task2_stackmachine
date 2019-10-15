////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

namespace xi {

    IntStack::IntStack(size_t sz)
    {
        _stack = new int[sz];
        _ssize = sz;
        _head = 0;
    }

    IntStack::~IntStack()
    {
        delete[] _stack;
    }

    void IntStack::push(int el)
    {
        if (isFull())
            throw std::logic_error("Stack is full");

        _stack[_head++] = el;
    }

    int IntStack::pop()
    {
        if (isEmpty())
            throw std::logic_error("Stack is empty");

        return _stack[--_head];
    }

    bool IntStack::isFull() const
    {
        return _ssize == _head;
    }

    bool IntStack::isEmpty() const
    {
        return _head == 0;
    }

    int IntStack::top()
    {
        if (isEmpty())
            throw std::logic_error("Stack is empty");

        return _stack[_head - 1];
    }

    void IntStack::clear()
    {
        _head = 0;
    }
} // namespace xi

