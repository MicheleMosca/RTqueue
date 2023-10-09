#ifndef FIFOlinkedqueue
#define FIFOlinkedqueue

#include <LinkedQueue.h>
#include <iostream>

//! define UNLIMITED value for dimension
#define UNLIMITED -1

//! Definition of a LinkedQueue based on FIFO schedular's rule

template <class T> class FIFOLinkedQueue : public LinkedQueue<T> {  
    public:
        //! Constructor of a FIFOLinkedQueue.
        //! blocked and dimension are unmandatory values.
        //! Default value for blocked are true (Push and Pop function will be blocked functions).
        //! Default value for dimension are UNLIMITED.
        FIFOLinkedQueue(int dimension = UNLIMITED, bool blocked = true) : LinkedQueue<T>(dimension, blocked){}

        //! Insert a new element inside the FIFOLinkedQueue
        void push(T element)
        {
            //! mutex for critical section
            pthread_mutex_lock(&this->mutex);

            //! Dimension control and check if block is set
            if(this->count == this->dimension && !this->blocked){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is full");
            }

            //! Wait condition: queue is full
            while(this->count == this->dimension){
                pthread_cond_wait(&this->conditionPop, &this->mutex);
            }

            //! Insert the new element inside the queue
            Node<T>* tmp = new Node<T>();
            tmp->setData(element);
            tmp->setNext(NULL);

            if (this->empty()) {
                this->first = this->last = tmp;
            }
            else {
                this->last->setNext(tmp);
                this->last = tmp;
            }

            //! Update the number of elements inside the queue
            this->count++;

            //! Signal push done
            pthread_cond_signal(&this->conditionPush);

            //! Leave the critical section
            pthread_mutex_unlock(&this->mutex);
        }

        //! Extract the first element that was insert into the FIFOLinkedQueue
        T pop(void)
        {
            //! Mutex for critical section
            pthread_mutex_lock(&this->mutex);

            //! Empty control and check if block is set
            if ( this->empty() && !this->blocked ){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //! Wait condition: queue is empty
            while (this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }
                
            //! Extract an element
            T ret = this->first->getData();
            Node<T>* tmp = this->first;
            this->first = this->first->getNext();
            delete tmp;

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
            if(this->empty()){
                throw std::logic_error("Queue is empty");
            }

            // Take a single element of the queue and print it
            Node<T>* current = this->first;
            while (current->getNext()) {
                std::cout << current->getData() << ' ';
                current = current->getNext();
            }
            std::cout << current->getData() << std::endl;
        }
};

#endif