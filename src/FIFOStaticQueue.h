#ifndef FIFOstaticqueue
#define FIFOstaticqueue

#include <StaticQueue.h>
#include <iostream>

template <class T> class FIFOStaticQueue : public StaticQueue<T> {  
    
    public:
        FIFOStaticQueue(){}

        FIFOStaticQueue(size_t dimension, bool blocked = true) : StaticQueue<T>(dimension, blocked){}

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

        void printQueue(){
            size_t i;
            std::cout << "[ ";
            for(i = 0; i < this->count; i++)
                std::cout << this->queue[i] << " ";
            std::cout << " ]" << std::endl;
        }
};

#endif