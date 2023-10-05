#ifndef LIFOstaticqueue
#define LIFOstaticqueue

#include <StaticQueue.h>
#include <iostream>

template <class T> class LIFOStaticQueue : public StaticQueue<T> {  
    
    public:
        LIFOStaticQueue(){}

        LIFOStaticQueue(size_t dimension, bool blocked = true) : StaticQueue<T>(dimension, blocked){}

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
                std::cout << "push full" << std::endl;
                pthread_cond_wait(&this->conditionPop, &this->mutex);
            }

            int i;
            for(i = this->count; i >= 0; i--){
                this->queue[i + 1] = this->queue[i];
            }
            this->queue[0] = element;
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
            
            // this->printQueue();
            T ret = this->front();
            size_t i;
            for(i = 0; i <= this->count; i++){
                this->queue[i] = this->queue[i + 1];
            }

            //ripulisco la coda
            for(i = this->count; i <= this->dimension; i++)
                this->queue[i] = 0;
            
            this->lastElem = (this->lastElem - 1) % this->dimension;

            this->count--;

            pthread_cond_signal(&this->conditionPop);

            pthread_mutex_unlock(&this->mutex);

            return ret;
        }

        void printQueue(){
            size_t i;
            std::cout << "[ ";
            for(i = 0; i < this->dimension; i++)
                std::cout << this->queue[i] << " ";
            std::cout << "]" << std::endl;
        }
};

#endif