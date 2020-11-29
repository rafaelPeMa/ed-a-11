#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include <string>

template <class T>
class Queue {

    private:

        class Node {
            private:
                T data;
                Node* next;
                Node* prev;

            public:
                Node();
                Node(const T&);

                T getData() const;
                Node* getNext() const;
                Node* getPrev() const;

                void setData(const T&);
                void setNext(Node*);
                void setPrev(Node*);
            };

        Node* header;

        void copyAll(const Queue<T>&);
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

        Queue();
        Queue(const Queue<T>&);
        ~Queue();

        bool isEmpty() const;

        void enqueue(const T&);

        T dequeue();

        T getFront();

        Queue<T>& operator = (const Queue<T>&);
    };

template<class T>
Queue<T>::Node::Node() : next(nullptr), prev(nullptr) { }

template<class T>
Queue<T>::Node::Node(const T& t) : data(t), next(nullptr), prev(nullptr) { }

template<class T>
T Queue<T>::Node::getData() const {
    return data;
    }

template<class T>
typename Queue<T>::Node* Queue<T>::Node::getNext() const {
    return next;
    }

template<class T>
typename Queue<T>::Node* Queue<T>::Node::getPrev() const {
    return prev;
    }

template<class T>
void Queue<T>::Node::setData(const T& t) {
    data = t;
    }

template<class T>
void Queue<T>::Node::setNext(Node* n) {
    next = n;
    }

template<class T>
void Queue<T>::Node::setPrev(Node* p) {
    prev = p;
    }

template <class T>
void Queue<T>::copyAll(const Queue<T>& q) {
    Node* aux(q.header->getNext());
    Node* newNode;
    Node* last(header);

    while ( aux != q.header ) {
        newNode = new Node(aux->getData());
        if ( newNode == nullptr ) {
            throw Exception("Memoria no disponible, copyAll");
            }
        newNode->setPrev(last);
        last->setNext(newNode);
        last = newNode;
        aux = aux->getNext();
        }
    last->setNext(header);
    header->setPrev(last);
    }

template <class T>
void Queue<T>::deleteAll() {
    Node* aux;
    while ( header->getNext() != header ) {
            aux = header->getNext();
            header->setNext(aux->getNext());
            delete aux;
        }
    }

template <class T>
Queue<T>::Queue() : header(new Node()) {
    if ( header == nullptr ) {
        throw Exception("Memoria no disponible, Queue");
    }
    header->setNext(header);
    header->setPrev(header);
}

template <class T>
Queue<T>::Queue(const Queue<T>& q) : Queue() {
    copyAll(q);
    }

template <class T>
Queue<T>::~Queue() {
    deleteAll();
    }

template <class T>
bool Queue<T>::isEmpty() const {
    return header->getNext() == header;
    }

template <class T>
void Queue<T>::enqueue(const T& t) {
    Node* aux = new Node(t);
    if ( aux == nullptr ) {
        throw Exception("Memoria no disponible, enqueue");
        }
    aux->setPrev(header->getPrev());
    aux->setNext(header);
    header->getPrev()->setNext(aux);
    header->setPrev(aux);
    }

template <class T>
T Queue<T>::dequeue() {
    if ( isEmpty() ) {
        throw Exception("Insuficiencia de datos, dequeue");
        }
    T t(header->getNext()->getData());
    Node* aux(header->getNext());

    header->setNext(aux->getNext());
    aux->getNext()->setPrev(header);

    delete aux;
    return t;
    }

template <class T>
T Queue<T>::getFront() {
    if ( isEmpty() ) {
        throw Exception("Insuficiencia de datos, getFront");
        }
    return header->getNext()->getData();
    }

template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& q) {
    deleteAll();
    copyAll(q);

    return *this;
    }

#endif // QUEUE_H_INCLUDED
