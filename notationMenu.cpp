#include "notationMenu.h"

using namespace std;

void NotationMenu::stringToQueue(std::string s) {
    char c;

    for ( int i(0); i < s.length(); i++) {
        c = s[i];
        infix.enqueue(c);
        }
    infix.enqueue('\0');
    }

void NotationMenu::getExpression() {
    string myString;

    cout << "Conversion de notacion Infija a Posfija" << endl;
    cout << "Ingrese la expresion a convertir: ";
    getline(cin,myString);

    stringToQueue(myString);
    }

void NotationMenu::infixToPostfixed() {
    char c;

    while ( !infix.isEmpty() ) {
        c = infix.dequeue();

        if ( c == '(' ) {
            myStack.push(c);
            continue;
            }

        if ( c == ')' ) {
            while ( !myStack.isEmpty() ) {
                if (myStack.getTop() == '(') {
                    myStack.pop();
                    break;
                    }
                postFixed.enqueue(myStack.pop());
                }
            continue;
            }

        if ( c == '\0' ) {
            while ( !myStack.isEmpty() ) {
                postFixed.enqueue(myStack.pop());
                }
            continue;
            }

        if ( c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            switch( c ) {
                case '+' :
                case '-': {
                    while ( !myStack.isEmpty() ) {
                        if (myStack.getTop() == '(' ) {
                            break;
                            }
                        while ( myStack.getTop() == '+' || myStack.getTop() == '-' || myStack.getTop() == '*' || myStack.getTop() == '/'|| myStack.getTop() == '^') {
                            postFixed.enqueue(myStack.pop());
                            if ( myStack.isEmpty() ) {
                                break;
                                }
                            }
                        break;
                        }
                    myStack.push(c);
                    }
                break;
                case '*' :
                case '/' : {
                    while ( !myStack.isEmpty() ) {
                        if (myStack.getTop() == '(' ) {
                            break;
                            }
                        while ( myStack.getTop() == '*' || myStack.getTop() == '/' || myStack.getTop() == '^') {
                            postFixed.enqueue(myStack.pop());
                            if ( myStack.isEmpty() ) {
                                break;
                                }
                            }
                        break;
                        }
                    myStack.push(c);
                    }
                break;
                case '^' : {
                    while ( !myStack.isEmpty() ) {
                        if (myStack.getTop() == '(' ) {
                            break;
                            }
                        while ( myStack.getTop() == '^' ) {
                            postFixed.enqueue(myStack.pop());
                            if ( myStack.isEmpty() ) {
                                break;
                                }
                            }
                        break;
                        }

                    myStack.push(c);
                    }
                break;
                }
            continue;
            }

        postFixed.enqueue(c);

        }

    }

void NotationMenu::showResult() {
    cout << endl << "Notacion posfija: " << endl;
    while ( !postFixed.isEmpty() ) {
        cout << postFixed.dequeue();
        }
    cout << endl << endl;
    }

NotationMenu::NotationMenu() : infix(), postFixed(), myStack() {
    getExpression();
    infixToPostfixed();
    showResult();
    }

