#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <string>

///Declaracion

class StackException : public std::exception {

    private:
        std::string msg;

    public:
        explicit StackException(const char* message) : msg(message) { }

        explicit StackException(const std::string& message) : msg(message) { }

        virtual ~StackException() throw () { }

        virtual const char* what() const throw () {
            return msg.c_str();
            }
    };

template<class T, int SIZE = 1024>
class Stack {

    private:
        T data[SIZE];
        int top;

        void copyAll(const Stack<T, SIZE>&);

    public:
        Stack();
        Stack(const Stack<T, SIZE>&);

        bool isEmpty() const;
        bool isFull() const;

        void push(const T&);

        T pop();

        T getTop();

        Stack<T, SIZE>& operator = (const Stack<T, SIZE>&);
    };

///Implementacion

using namespace std;

template<class T, int SIZE>
void Stack<T, SIZE>::copyAll(const Stack<T, SIZE>& s) {
    int i(0);
    while ( i <= s.top ) {
        data[i] = s.data[i];
        i++;
        }
    top = s.top;
    }

template<class T, int SIZE>
Stack<T, SIZE>::Stack() : top(-1) { }

template<class T, int SIZE>
Stack<T, SIZE>::Stack(const Stack<T, SIZE>& s) {
    copyAll(s);
    }

template<class T, int SIZE>
Stack<T, SIZE>& Stack<T, SIZE>::operator = (const Stack<T, SIZE>& s) {
    copyAll(s);
    return *this;
    }

template<class T, int SIZE>
bool Stack<T, SIZE>::isEmpty() const {
    return top == -1;
    }

template<class T, int SIZE>
bool Stack<T, SIZE>::isFull() const {
    return top == SIZE - 1;
    }

template<class T, int SIZE>
void Stack<T, SIZE>::push(const T& a) {
    if ( isFull() ) {
        throw StackException("Desbordamiento de datos, push");
        }
    data[++top] = a;
    }

template<class T, int SIZE>
T Stack<T, SIZE>::pop() {
    if ( isEmpty() ) {
        throw StackException("Insuficiencia de datos, pop");
        }
    return data[top--];
    }

template<class T, int SIZE>
T Stack<T, SIZE>::getTop() {
    if ( isEmpty() ) {
        throw StackException("Insuficiencia de datos, getTop");
        }
    return data[top];
    }

#endif // STACK_H_INCLUDED
