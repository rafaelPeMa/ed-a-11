#ifndef NOTATIONMENU_H_INCLUDED
#define NOTATIONMENU_H_INCLUDED

#include <iostream>
#include <string>

#include "stack.h"
#include "queue.h"

class NotationMenu {

    private:
        Queue<char> infix;
        Queue<char> postFixed;
        Stack<char> myStack;
        void stringToQueue(std::string);
        void getExpression();
        void infixToPostfixed();
        void showResult();

    public:
        NotationMenu();

    };

#endif // NOTATIONMENU_H_INCLUDED
