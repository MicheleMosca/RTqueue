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
            pthread_mutex_lock(&this->mutex);

            if(this->count == this->dimension && !this->blocked){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is full");
            }

            // if the queue is full => block
            while(this->count == this->dimension){
                pthread_cond_wait(&this->conditionPop, &this->mutex);
            }

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
            this->count++;

            pthread_cond_signal(&this->conditionPush);

            pthread_mutex_unlock(&this->mutex);
        }

        //! Extract the first element that was insert into the FIFOLinkedQueue
        T pop(void)
        {
            pthread_mutex_lock(&this->mutex);

            // release function if the queue is empty and unblocked function is enable
            if ( this->empty() && !this->blocked ){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //if the queue is empty => block
            while (this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }
                
            T ret = this->first->getData();
            Node<T>* tmp = this->first;
            this->first = this->first->getNext();
            this->count--;
            delete tmp;

            pthread_cond_signal(&this->conditionPop);

            pthread_mutex_unlock(&this->mutex);
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