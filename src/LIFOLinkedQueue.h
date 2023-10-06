#ifndef LIFOlinkedqueue
#define LIFOlinkedqueue

#include <node.h>
#include <iostream>

#define UNLIMITED -1

template <class T> class LIFOLinkedQueue : public LinkedQueue<T> {  
    public:
        LIFOLinkedQueue(int dimension = UNLIMITED, bool blocked = true, bool persistence = true) : LinkedQueue<T>(dimension, blocked, persistence){}

        void push(T element)
        {
            pthread_mutex_lock(&this->mutex);

            if(this->full() && !this->blocked && this->persistent()){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is full");
            }

            //if the queue is full => block
            while(this->full()){
                pthread_cond_wait(&this->conditionPop, &this->mutex);
            }

            // if element are not persistence and the queue is full, remove the element on bottom of the queue
            if (this->full() && !this->persistent())
            {
                Node<T>* tmp = this->first;
                this->first = this->first->getNext();
                delete tmp;
                this->count--;
            }

            //se la coda è vuota ne creo una nuova ...
            Node<T>* tmp = new Node<T>();
            if(this->empty()){
                this->first = this->last = tmp;
            }
            else{
                // ... altrimenti inserisco l'elemento in cima
                // NOTA: lo inserisco in cima per facilitare la pop
                tmp->setData(element);
                tmp->setNext(this->first);
                this->first = tmp;
            }

            this->count++;

            pthread_cond_signal(&this->conditionPush);

            pthread_mutex_unlock(&this->mutex);
        }

        T pop(void){
            pthread_mutex_lock(&this->mutex);

            /* release function if the queue is empty and unblocked function is enable */
            if ( this->empty() && !this->blocked ){
                pthread_mutex_unlock(&this->mutex);
                throw std::logic_error("Queue is empty");
            }

            //if the queue is empty => block
            while (this->empty()){
                pthread_cond_wait(&this->conditionPush, &this->mutex);
            }

            //recupero l'elemento in cima (l'ultimo inserito => LIFO)
            T ret = this->first->getData();

            //aggiorno la coda
            Node<T>* tmp = this->first;
            this->first = this->first->getNext();
            delete tmp;
            
            //printQueue();

            this->count --;

            pthread_cond_signal(&this->conditionPop);

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
};

#endif