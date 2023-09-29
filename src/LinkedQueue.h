#ifndef linkedqueue
#define linkedqueue

#include <node.h>
#include <iostream>
#include <pthread.h>

template <class T> class LinkedQueue {  
    protected:
        Node<T>* first;
        Node<T>* last;
        int count;
        pthread_cond_t conditionPush;
        pthread_cond_t conditionPop;
        pthread_mutex_t mutex;
        bool blocked;
        int dimension;
    
    public:
        LinkedQueue(bool blocked, int dimension){
            first = NULL;
            last = NULL;
            count = 0;
            conditionPush = PTHREAD_COND_INITIALIZER;
            conditionPop = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;

            /* Make the pop function blocked or unblocked */
            this->blocked = blocked;

            this->dimension = dimension;
        }

        virtual void push(T element) = 0;

        virtual T pop(void) = 0;

        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return first->getData();
        }

        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return last->getData();
        }

        int size(void){
            return this->count;
        }

        bool empty(void){
            return this->count == 0 ? true : false;
        }

        bool full(void){
            return this->count == this->dimension ? true : false;
        }
};

#endif