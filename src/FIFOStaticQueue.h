#ifndef FIFOstaticqueue
#define FIFOstaticqueue

#include <StaticQueue.h>
#include <iostream>

//! Definition of a StaticQueue based on FIFO schedular's rule

template <class T> class FIFOStaticQueue : public StaticQueue<T> {
    public:
        //! Dummy constructor of a FIFOStaticQueue (DON'T USE IT!)
        FIFOStaticQueue(){}

        //! Constructor of a FIFOStaticQueue.
        //! blocked is unmandatory value.
        //! Default value for blocked is true (Push and Pop function will be blocked functions).
        //! Dimension is the queue's dimension
        FIFOStaticQueue(size_t dimension, bool blocked = true, bool persistence = true) : StaticQueue<T>(dimension, blocked, persistence){}

        //! Insert a new element inside the FIFOStaticQueue
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

            // if element are not persistence and the queue is full, remove the element on top of the queue
            if (this->full() && !this->persistent())
            {
                this->firstElem = (this->firstElem + 1) % this->dimension;
                this->count--;
            }

            //! Insert the new element inside the queue
            this->queue[this->lastElem] = element;
            this->lastElem = (this->lastElem + 1) % this->dimension;

            //! Update the number of elements inside the queue
            this->count++;

            //! Signal push done
            pthread_cond_signal(&this->conditionPush);

            //! Leave the critical section
            pthread_mutex_unlock(&this->mutex);
        }

        //! Extract the first element that was insert into the FIFOStaticQueue
        T pop(void){
            //! Mutex for critical section
            pthread_mutex_lock(&this->mutex);
            
            //! Empty control and check if block is set
            if ( this->empty() && !this->blocked){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //! Wait condition: queue empty
            while(this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }
            
            //! Extract an element
            T ret = this->front();
            this->firstElem = (this->firstElem + 1) % this->dimension;

            //! Upgrade the number of elements inside the queue
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
            for(i = 0; i < this->count; i++)
                std::cout << this->queue[i] << " ";
            std::cout << " ]" << std::endl;
        }
};

#endif