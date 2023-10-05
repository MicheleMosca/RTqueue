#ifndef FIFOstaticqueue
#define FIFOstaticqueue

#include <StaticQueue.h>
#include <iostream>

//! Definition of a LinkedQueue based on FIFO schedular's rule

template <class T> class FIFOStaticQueue : public StaticQueue<T> {
    public:
        //! Dummy constructor (DON'T USE IT!)
        FIFOStaticQueue(){}

        //! Constructor of a FIFOStaticQueue.
        //! blocked is unmandatory value.
        //! Default value for blocked are true (Push and Pop function will be blocked functions).
        //! Dimension is the queue's dimension
        FIFOStaticQueue(size_t dimension, bool blocked = true) : StaticQueue<T>(dimension, blocked){}

        //! Insert a new element inside the FIFOStaticQueue
        void push(T element)
        {
            pthread_mutex_lock(&this->mutex);

            //dimension control
            if(this->full() && !this->blocked){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is full");
            }

            //blocked condition
            while(this->full()){
                pthread_cond_wait(&this->conditionPop, &this->mutex);
            }

            this->queue[this->lastElem] = element;
            this->lastElem = (this->lastElem + 1) % this->dimension;

            // this->printQueue();
            
            this->count++;

            pthread_cond_signal(&this->conditionPush);

            pthread_mutex_unlock(&this->mutex);
        }

        //! Extract the first element that was insert into the FIFOStaticQueue
        T pop(void){
            pthread_mutex_lock(&this->mutex);
            
            //empty control
            if ( this->empty() && !this->blocked){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //block condition
            while(this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }
            
            T ret = this->front();
            this->firstElem = (this->firstElem + 1) % this->dimension;

            this->count--;

            // this->printQueue();

            pthread_cond_signal(&this->conditionPop);

            pthread_mutex_unlock(&this->mutex);

            return ret;
        }

        //! Print to the standard output the current state of the queue. It used only for debug purpose
        void printQueue(){
            size_t i;
            std::cout << "[ ";
            for(i = 0; i < this->count; i++)
                std::cout << this->queue[i] << " ";
            std::cout << " ]" << std::endl;
        }
};

#endif