#ifndef LIFOlinkedqueue
#define LIFOlinkedqueue

#include <node.h>
#include <iostream>

#define UNLIMITED -1

//! Structure definition of a LIFOLinkedQueue

template <class T> class LIFOLinkedQueue : public LinkedQueue<T> {  
    public:
        //! Constructor of a LIFOLinkedQueue
        //! blocked and dimensione are mandatory value
        LIFOLinkedQueue(int dimension = UNLIMITED, bool blocked = true) : LinkedQueue<T>(dimension, blocked){}

        //! push method for insert a new value
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

            //! Insert the new element in the queue
            Node<T>* tmp = new Node<T>();
            if(this->empty()){
                this->first = this->last = tmp;
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

        //! pop method for extract an alement
        T pop(void){
            //! Mutex for critical section
            pthread_mutex_lock(&this->mutex);

            //! empty control and check if block is set
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
            return ret;
        }

        //! printQueue method
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