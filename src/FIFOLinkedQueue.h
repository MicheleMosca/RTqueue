#ifndef FIFOlinkedqueue
#define FIFOlinkedqueue

#include <LinkedQueue.h>
#include <iostream>

#define UNLIMITED -1

template <class T> class FIFOLinkedQueue : public LinkedQueue<T> {  
    public:
        FIFOLinkedQueue(bool blocked = true, int dimension = UNLIMITED) : LinkedQueue<T>(blocked, dimension){}

        void push(T element)
        {
            pthread_mutex_lock(&this->mutex);

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

            pthread_cond_signal(&this->condition);

            pthread_mutex_unlock(&this->mutex);
        }

        T pop(void)
        {
            pthread_mutex_lock(&this->mutex);

            /* release function if the queue is empty and unblocked function is enable */
            if ( this->empty() && !this->blocked ){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            if (this->empty()){
                pthread_cond_wait(&this->condition, &this->mutex);
            }
                
            T ret = this->first->getData();
            Node<T>* tmp = this->first;
            this->first = this->first->getNext();
            this->count--;
            delete tmp;

            pthread_mutex_unlock(&this->mutex);
            return ret;
        }

        void printQueue(){
            if(this->empty()){
                throw std::logic_error("Queue is empty");
            }

            //prendo la coda da stampare e la itero
            Node<T>* current = this->first;
            while (current->getNext()) {
                std::cout << current->getData() << ' ';
                current = current->getNext();
            }
            std::cout << current->getData() << std::endl;
        }

        T front(void)
        {
            if (this->empty())
                throw std::logic_error("Queue is empty");
            return this->first->getData();
        }

        T back(void)
        {
            if (this->empty())
                throw std::logic_error("Queue is empty");
            return this->last->getData();
        }
};

#endif