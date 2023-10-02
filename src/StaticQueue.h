#ifndef StaticQueue_H
#define StaticQueue_H

#include <iostream>
#include <pthread.h>

//! Struture definition of a StaticQueue

template <class T> class StaticQueue {  
    protected:
        //! Definition on the static queue
        T *queue;

        //! First element's index of the queue
        size_t firstElem;

        //! Last element's index of the queue
        size_t lastElem;

        //! Number of element inside the queue
        size_t count;

        //! Define the maximum dimension of the queue 
        size_t dimension;

        //! Condition variable to block thread or task waiting for a new Push function call
        pthread_cond_t conditionPush;

        //! Condition variable to block thread or task waiting for a new Pop function call
        pthread_cond_t conditionPop;

        //! Mutex semaphore to access to Push or Pop function in a Thread safe way
        pthread_mutex_t mutex;

        //! Define if the call of a Push or Pop function must be blocked or unblocked
        bool blocked;
    
    public:
        //! Constructor of a StaticQueue.
        //! blocked and dimension are mandatory value.
        StaticQueue(size_t dimension, bool blocked){
            this->dimension = dimension;
            queue = new T[this->dimension];
            this->firstElem = this->lastElem = 0;
            conditionPush = PTHREAD_COND_INITIALIZER;
            conditionPop = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;
            count = 0;
            this->blocked = blocked;
        }

        //! Insert a new element inside the StaticQueue
        virtual void push(T element) = 0;

        //! Extract an element of the StaticQueue
        virtual T pop(void) = 0;

        //! Get the element of in front of the queue without remove it
        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return this->queue[this->firstElem];
        }

        //! Get the element of in back of the queue without remove it
        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return this->queue[this->lastElem];
        }

        //! Get the current size of the queue (number of element inside)
        int size(void){
            return this->dimension;
        }

        //! Return if the queue is empty
        bool empty(void){
            return this->firstElem == this->lastElem && this->count == 0 ? true : false;
        }

        //! Return if the queue is full
        bool full(void){
            return this->firstElem == this->lastElem && this->count == this->dimension ? true : false;
        }
};

#endif