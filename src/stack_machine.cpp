////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

    void checkWordCorrectness(std::string word)
    {
        for (int i = 0; i < word.length(); ++i)
        {
            if (word[i] < '0' || word[i] > '9')
            {
                throw std::exception();
            }
        }
    }

//==============================================================================
// class PlusOp
//==============================================================================

    int PlusOp::operation(char op, int a, int b,
                          int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
    {
        if (op != '+')
            throw std::logic_error("Operation other than Plus (+) are not supported");

        // here we just ignore unused operands
        return a + b;
    }

    IOperation::Arity PlusOp::getArity() const
    {
        return arDue;
    }

//==============================================================================
// class MultOp
//==============================================================================

    int MultOp::operation(char op, int a, int b, int /*c*/)
    {
        if (op != '*')
            throw std::logic_error("Operation other than Mult (*) are not supported");

        return a * b;
    }

    IOperation::Arity MultOp::getArity() const
    {
        return arDue;
    }

//==============================================================================
// class ChoiceOp
//==============================================================================

    int ChoiceOp::operation(char op, int a, int b, int c)
    {
        if (op != '?')
            throw std::logic_error("Operation other than Choice (?) are not supported");

        return a != 0 ? b : c;
    }


    IOperation::Arity ChoiceOp::getArity() const
    {
        return arTre;
    }

//==============================================================================
// class AssignOp
//==============================================================================

    int AssignOp::operation(char op, int a, int /*b*/, int /*c*/)
    {
        if (op != '=')
            throw std::logic_error("Operation other than Assign (=) are not supported");

        return a;
    }

    IOperation::Arity AssignOp::getArity() const
    {
        return arUno;
    }

//==============================================================================
// class StackMachine
//==============================================================================

    void StackMachine::registerOperation(char symb, xi::IOperation* oper)
    {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it != _opers.end())
            throw std::logic_error("This operation is already registered");

        _opers[symb] = oper;
    }

    IOperation* StackMachine::getOperation(char symb)
    {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it == _opers.end())
            return nullptr;

        return _opers[symb];
    }

    int StackMachine::calculate(const std::string& expr, bool clearStack)
    {
        std::stringstream stringstream(expr);
        std::string word;

        if (clearStack)
            _s.clear();

        while (!stringstream.eof())
        {
            stringstream >> word;
            IOperation* operation = getOperation(word[0]);

            if (operation && (word.length() != 1))
                operation = nullptr;

            if (operation)
            {
                int n = operation->getArity() + 1;
                int* args = new int[n];
                for (int i = n - 1; i >= 0; --i)
                {
                    args[i] = _s.pop();
                }

                _s.push(operation->operation(word[0], args[0], args[1], args[2]));
            } else
            {
                checkWordCorrectness(word);
                _s.push(std::stoi(word));
            }
        }

        return _s.top();
    }

} // namespace xi
