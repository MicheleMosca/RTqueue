#ifndef LIFOlinkedqueue
#define LIFOlinkedqueue

#include <node.h>
#include <iostream>

//! define UNLIMITED value for dimension
#define UNLIMITED -1

//! Structure of a LinkedQueue based on LIFO shedular's rule

template <class T> class LIFOLinkedQueue : public LinkedQueue<T> {  
    public:
        //! Constructor of a LIFOLinkedQueue
        //! blocked and dimensione are mandatory values
        //! Default value for blocked is true (Push and Pop function will be blocked functions)
        //! Default value for dimension is UNLIMITED
        LIFOLinkedQueue(int dimension = UNLIMITED, bool blocked = true, bool persistence = true) : LinkedQueue<T>(dimension, blocked, persistence){}

        //! Insert a new element inside the LIFOLinkedQueue
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

            //! If element are not persistence and the queue is full, remove the element on bottom of the queue
            if (this->full() && !this->persistent())
            {
                Node<T>* current = this->first; 
                while (current->getNext() != this->last && current->getNext() != nullptr)
                    current = current->getNext();

                Node<T>* tmp = this->last;
                this->last = current;
                this->last->setNext(nullptr);
                delete tmp;
                this->count--;
            }

            //! Insert the new element in the queue
            Node<T>* tmp = new Node<T>();
            if(this->empty()){
                this->first = this->last = tmp;
                tmp->setData(element);
            }
            else{
                tmp->setData(element);
                tmp->setNext(this->first);
                this->first = tmp;
            }

            //! Update the number of elements inside the queue
            this->count++;

            //! Signal push done
            pthread_cond_signal(&this->conditionPush);

            //! Leave the critical section
            pthread_mutex_unlock(&this->mutex);
        }

        //! Extract the last element that was insert into the LIFOLinkedQueue
        T pop(void){
            //! Mutex for critical section
            pthread_mutex_lock(&this->mutex);

            //! Empty control and check if block is set
            if ( this->empty() && !this->blocked ){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //! Wait condition: queue empty
            while (this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }

            //! Extract an element
            T ret = this->first->getData();

            //! Update the queue
            Node<T>* tmp = this->first;
            this->first = this->first->getNext();
            delete tmp;
            
            //! Update the number of elements inside the queue
            this->count --;

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

            Node<T>* current = this->first;
            while (current->getNext()) {
                std::cout << current->getData() << ' ';
                current = current->getNext();
            }
            std::cout << current->getData() << std::endl;
        }
};

#endif