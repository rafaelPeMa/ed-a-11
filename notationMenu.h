#ifndef NOTATIONMENU_H_INCLUDED
#define NOTATIONMENU_H_INCLUDED

#define LIMIT_QUEUE 100
#define LIMIT_STACK 20

#include <iostream>
#include <string>

#include "stack.h"
#include "queue.h"

class NotationMenu {

    private:
        Queue<char,LIMIT_QUEUE> infix;
        Queue<char,LIMIT_QUEUE> postFixed;
        Stack<char,LIMIT_STACK> myStack;
        void stringToQueue(std::string);
        void getExpression();
        void infixToPostfixed();
        void showResult();

    public:
        NotationMenu();

    };

#endif // NOTATIONMENU_H_INCLUDED
