#ifndef staticqueue
#define staticqueue

#include <iostream>
#include <pthread.h>

template <class T> class StaticQueue {  
    protected:
        T *queue;
        size_t firstElem;
        size_t lastElem;
        size_t dimension;
        pthread_cond_t conditionPush;
        pthread_cond_t conditionPop;
        pthread_mutex_t mutex;
        bool blocked;
        size_t count;
    
    public:
        StaticQueue(size_t dimension, bool blocked = true){
            this->dimension = dimension;
            queue = new T[this->dimension];
            this->firstElem = this->lastElem = 0;
            conditionPush = PTHREAD_COND_INITIALIZER;
            conditionPop = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;
            count = 0;
            this->blocked = blocked;
        }

        virtual void push(T element) = 0;

        virtual T pop(void) = 0;

        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return this->queue[this->firstElem];
        }

        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return this->queue[this->lastElem - 1];
        }

        int size(void){
            return this->dimension;
        }

        bool empty(void){
            return this->firstElem == this->lastElem && this->count == 0 ? true : false;
        }

        bool full(void){
            return this->firstElem == this->lastElem && this->count == this->dimension ? true : false;
        }
};

#endif