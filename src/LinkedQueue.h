#ifndef linkedqueue
#define linkedqueue

#include <node.h>
#include <iostream>
#include <pthread.h>

//! Struture definition of a LinkedQueue

template <class T> class LinkedQueue {  
    protected:
        //! First element of the queue
        Node<T>* first;

        //! Last element of the queue
        Node<T>* last;

        //! Number of element inside the queue
        int count;

        //! Condition variable to block thread or task waiting for a new Push function call
        pthread_cond_t conditionPush;

        //! Condition variable to block thread or task waiting for a new Pop function call
        pthread_cond_t conditionPop;

        //! Mutex semaphore to access to Push or Pop function in a Thread safe way
        pthread_mutex_t mutex;

        //! Define if the call of a Push or Pop function must be blocked or unblocked
        bool blocked;

        //! Define the maximum dimension of the queue 
        int dimension;
    
    public:
        //! Constructor of a LinkedQueue.
        //! blocked and dimension are mandatory value.
        LinkedQueue(bool blocked, int dimension){
            first = NULL;
            last = NULL;
            count = 0;
            conditionPush = PTHREAD_COND_INITIALIZER;
            conditionPop = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;
            this->blocked = blocked;
            this->dimension = dimension;
        }

        //! Insert a new element inside the LinkedQueue
        virtual void push(T element) = 0;

        //! Extract an element of the LinkedQueue
        virtual T pop(void) = 0;

        //! Get the element of in front of the queue without remove it
        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return first->getData();
        }

        //! Get the element of in back of the queue without remove it
        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return last->getData();
        }

        //! Get the current size of the queue (number of element inside)
        int size(void){
            return this->count;
        }

        //! Return if the queue is empty
        bool empty(void){
            return this->count == 0 ? true : false;
        }

        //! Return if the queue is full
        bool full(void){
            return this->count == this->dimension ? true : false;
        }
};

#endif