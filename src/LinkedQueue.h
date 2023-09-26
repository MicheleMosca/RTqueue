#ifndef linkedqueue
#define linkedqueue

#include <node.h>

template <class T> class LinkedQueue {  
    protected:
        Node<T>* first;
        Node<T>* last;
        int count;
        pthread_cond_t condition;
        pthread_mutex_t mutex;
        bool blocked;
        int dimension;
    
    public:
        LinkedQueue(bool blocked, int dimension){
            first = NULL;
            last = NULL;
            count = 0;
            condition = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;

            /* Make the pop function blocked or unblocked */
            this->blocked = blocked;

            this->dimension = dimension;
        }

        virtual void push(T element) = 0;

        virtual T pop(void) = 0;

        virtual T front(void) = 0;

        virtual T back(void) = 0;

        int size(void){
            return this->count;
        }

        bool empty(void){
            return this->count == 0 ? true : false;
        }

};

#endif