#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include <string>

///Declaracion

class QueueException : public std::exception {

    private:
        std::string msg;

    public:
        explicit QueueException(const char* message) : msg(message) { }

        explicit QueueException(const std::string& message) : msg(message) { }

        virtual ~QueueException() throw () { }

        virtual const char* what() const throw () {
            return msg.c_str();
            }
    };

template <class T, int SIZE = 1024>
class Queue {

    private:
        T data[SIZE];
        int frontPos;
        int endPos;

        void copyAll(const Queue<T, SIZE>&);

    public:
        Queue();
        Queue(const Queue<T, SIZE>&);

        bool isEmpty() const;
        bool isFull() const;

        void enqueue(const T&);

        T dequeue();

        T getFront();

        Queue<T, SIZE>& operator = (const Queue<T, SIZE>&);
    };

///Implementacion

using namespace std;

template <class T, int SIZE>
void Queue<T, SIZE>::copyAll(const Queue<T, SIZE>& q) {
    int i;
    if (endPos < frontPos) {
        i = frontPos;
        while (i < SIZE) {
            data[i] = q.data[i];
            i++;
            }
        i = 0;
        while (i <= endPos) {
            data[i] = q.data[i];
            i++;
            }
        }
    else {
        i = frontPos;
        while (i <= endPos) {
            data[i] = q.data[i];
            i++;
            }
        }
    endPos = q.endPos;
    frontPos = q.frontPos;
    }

template <class T, int SIZE>
Queue<T, SIZE>::Queue() : frontPos(0), endPos( SIZE - 1 ) { }

template <class T, int SIZE>
Queue<T, SIZE>::Queue(const Queue<T, SIZE>& q) {
    copyAll(q);
    }

template <class T, int SIZE>
Queue<T, SIZE>& Queue<T, SIZE>::operator = (const Queue<T, SIZE>& q) {
    copyAll(q);

    return *this;
    }

template <class T, int SIZE>
bool Queue<T, SIZE>::isEmpty() const {
    return ( frontPos == 0 and endPos == SIZE - 1)
           or ( frontPos == endPos + 1 );
    }

template <class T, int SIZE>
bool Queue<T, SIZE>::isFull() const {
    return ( frontPos == 0 and endPos == SIZE - 2)
           or ( frontPos == 1 and endPos == SIZE - 1 )
           or ( frontPos == endPos + 2 );
    }

template <class T, int SIZE>
void Queue<T, SIZE>::enqueue(const T& a) {
    if ( isFull() ) {
        throw QueueException("Desbordamiento de datos, enqueue");
        }

    if ( ++endPos == SIZE  ) {
        endPos = 0;
        }

    data[endPos] = a;
    }

template <class T, int SIZE>
T Queue<T, SIZE>::dequeue() {
    if ( isEmpty() ) {
        throw QueueException("Insuficiencia de datos, dequeue");
        }

    T e(data[frontPos]);

    if ( ++frontPos == SIZE) {
        frontPos = 0;
        }

    return e;
    }

template <class T, int SIZE>
T Queue<T, SIZE>::getFront() {
    if ( isEmpty() ) {
        throw QueueException("Insuficiencia de datos, getFront");
        }

    return data[frontPos];
    }

#endif // QUEUE_H_INCLUDED
