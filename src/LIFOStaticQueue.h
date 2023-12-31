#ifndef LIFOstaticqueue
#define LIFOstaticqueue

#include <StaticQueue.h>
#include <iostream>

//! Definition of a StaticQueue based on LIFO shedular's rule

template <class T> class LIFOStaticQueue : public StaticQueue<T> {  
    
    public:
        //! Dummy contructor of a LIFOStaticQueue (DON'T USE IT!)
        LIFOStaticQueue(){}

        //! Constructor of a LIFOStaticQueue
        //! blocked and dimension are mandatory value
        //! Default value for blocked is true (Push and Pop function will be blocked functions)
        LIFOStaticQueue(size_t dimension, bool blocked = true, bool persistence = true) : StaticQueue<T>(dimension, blocked, persistence){}

        //! Insert a new element inside the LIFOStaticQueue
        void push(T element)
        {
            //! Mutex for critical section
            pthread_mutex_lock(&this->mutex);

            //! Dimension control and check if block is set
            if(this->full() && !this->blocked && this->persistent()){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is full");
            }

            //! Wait condition: queue is full
            while(this->full() && this->persistent()){
                pthread_cond_wait(&this->conditionPop, &this->mutex);
            }

            // if element are not persistence and the queue is full, remove the element on bottom of the queue
            if (this->full() && !this->persistent())
            {   
                this->lastElem = (this->lastElem + (this->dimension -1)) % this->dimension;
                this->count--;
            }

            //! Insert the new element in the queue
            for(size_t i = this->dimension -1; i > 0; i--){
                this->queue[i] = this->queue[i - 1];
            }
            this->queue[0] = element;
            this->lastElem = (this->lastElem + 1) % this->dimension;
            
            //! Update the number of elements inside the queue
            this->count++;
           
            //! Signal push done
            pthread_cond_signal(&this->conditionPush);

            //! Leave the critical section
            pthread_mutex_unlock(&this->mutex);
        }

        //! Extract the last element that was insert into the LIFOStaticQueue
        T pop(void){
            //! Mutex for critical section
            pthread_mutex_lock(&this->mutex);
            
            //! Empty control and check if block is set
            if ( this->empty() && !this->blocked){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //! wait condition: queue empty
            while(this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }
            
            //! Extract an element
            T ret = this->front();
            for(size_t i = 0; i < this->count; i++){
                this->queue[i] = this->queue[i + 1];
            }
            
            //! Update last element index of the queue
            this->lastElem = (this->lastElem + (this->dimension -1)) % this->dimension;
          
            //! Update the number of elements inside the queue
            this->count--;
          
            //! Signal pop done
            pthread_cond_signal(&this->conditionPop);

            //! Leave the critical section
            pthread_mutex_unlock(&this->mutex);

            //! Return the element
            return ret;
        }

        //! Print to the standard output the current state of the queue. It used only for debug purpose
        void printQueue(){
            size_t i;
            std::cout << "[ ";
            for(i = 0; i < this->dimension; i++)
                std::cout << this->queue[i] << " ";
            std::cout << "]" << std::endl;
        }
};

#endif