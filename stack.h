#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <string>

template<class T>
class Stack {

    private:
        class Node {
            private:
                T data;
                Node* next;
            public:
                Node();
                Node(const T&);

                T getData() const;
                Node* getNext() const;

                void setData(const T&);
                void setNext(Node*);
            };

        Node* anchor;

        void copyAll(const Stack<T>&);
        void deleteAll();

    public:

        class Exception : public std::exception {
            private:
                std::string msg;
            public:
                explicit Exception(const char* message) : msg(message) { }

                explicit Exception(const std::string& message) : msg(message) { }

                virtual ~Exception() throw () { }

                virtual const char* what() const throw () {
                    return msg.c_str();
                    }
            };

        Stack();
        Stack(const Stack<T>&);
        ~Stack();

        bool isEmpty() const;

        void push(const T&);

        T pop();

        T getTop();

        Stack<T>& operator = (const Stack<T>&);
    };

template<class T>
Stack<T>::Node::Node() : next(nullptr) { }

template<class T>
Stack<T>::Node::Node(const T& t) : data(t), next(nullptr) { }

template<class T>
T Stack<T>::Node::getData() const {
    return data;
    }

template<class T>
typename Stack<T>::Node* Stack<T>::Node::getNext() const {
    return next;
    }

template<class T>
void Stack<T>::Node::setData(const T& t) {
    data = t;
    }

template<class T>
void Stack<T>::Node::setNext(Node* n) {
    next = n;
    }

template<class T>
void Stack<T>::copyAll(const Stack<T>& s) {
    Node* aux(s.anchor);
    Node* newNode;
    Node* last;

    if ( aux != nullptr ) {
        newNode = new Node(aux->getData());
        if ( newNode == nullptr ) {
            throw Exception("Memoria no disponible, copyAll");
            }
        anchor = newNode;
        last = newNode;
        aux = aux->getNext();
        while ( aux != nullptr ) {
            newNode = new Node(aux->getData());
            if ( newNode == nullptr ) {
                throw Exception("Memoria no disponible, copyAll");
                }
            last->setNext(newNode);
            last = newNode;
            aux = aux->getNext();
            }
        }
    }

template<class T>
void Stack<T>::deleteAll() {
    Node* aux;
    while ( anchor != nullptr ) {
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
        }
    }

template<class T>
Stack<T>::Stack() : anchor(nullptr) { }

template<class T>
Stack<T>::Stack(const Stack<T>& s) : anchor(nullptr) {
    copyAll(s);
    }

template<class T>
Stack<T>::~Stack() {
    deleteAll();
}

template<class T>
bool Stack<T>::isEmpty() const {
    return anchor == nullptr;
    }

template<class T>
void Stack<T>::push(const T& t) {
    Node* aux = new Node(t);
    if ( aux == nullptr ) {
        throw Exception("Memoria no disponible, push");
        }

    aux->setNext(anchor);
    anchor = aux;
    }

template<class T>
T Stack<T>::pop() {
    if ( isEmpty() ) {
        throw Exception("Insuficiencia de datos, pop");
        }
    T t(anchor->getData());
    Node* aux(anchor);
    anchor = anchor->getNext();
    delete aux;
    return t;
    }

template<class T>
T Stack<T>::getTop() {
    if ( isEmpty() ) {
        throw Exception("Insuficiencia de datos, getTop");
        }
    return anchor->getData();
    }

template<class T>
Stack<T>& Stack<T>::operator = (const Stack<T>& s) {
    deleteAll();
    copyAll(s);

    return *this;
    }

#endif // STACK_H_INCLUDED
