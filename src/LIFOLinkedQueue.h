#ifndef LIFOlinkedqueue
#define LIFOlinkedqueue

#include <node.h>
#include <iostream>

#define UNLIMITED -1

template <class T> class LIFOLinkedQueue : public LinkedQueue<T> {  
    public:
        LIFOLinkedQueue(bool blocked = true, int dimension = UNLIMITED) : LinkedQueue<T>(blocked, dimension){}

        void push(T element)
        {
            pthread_mutex_lock(&mutex);

            if(this->count == this->dimension && !blocked){
                pthread_mutex_unlock(&mutex);
                throw std::logic_error("Queue is full");
            }

            //if the queue is full => block
            while(this->count == this->dimension){
                pthread_cond_wait(&conditionPop, &mutex);
            }

            //se la coda è vuota ne creo una nuova ...
            Node<T>* tmp = new Node<T>();
            if(empty()){
                first = last = tmp;
            }
            else{
                // ... altrimenti inserisco l'elemento in cima
                // NOTA: lo inserisco in cima per facilitare la pop
                tmp->setData(element);
                tmp->setNext(first);
                first = tmp;
            }

            count++;

            pthread_cond_signal(&conditionPush);

            pthread_mutex_unlock(&mutex);
        }

        T pop(void){
            pthread_mutex_lock(&mutex);

            /* release function if the queue is empty and unblocked function is enable */
            if ( empty() && !blocked ){
                pthread_mutex_unlock(&mutex);
                throw std::logic_error("Queue is empty");
            }

            //if the queue is empty => block
            while (empty()){
                pthread_cond_wait(&conditionPush, &mutex);
            }

            //recupero l'elemento in cima (l'ultimo inserito => LIFO)
            T ret = first->getData();

            //aggiorno la coda
            Node<T>* tmp = first;
            first = first->getNext();
            delete tmp;
            
            //printQueue();

            count --;

            pthread_cond_signal(&conditionPop);

            pthread_mutex_unlock(&mutex);
            return ret;
        }

        void printQueue(){
            if(empty()){
                throw std::logic_error("Queue is empty");
            }

            //prendo la coda da stampare e la itero
            Node<T>* current = first;
            while (current->getNext()) {
                std::cout << current->getData() << ' ';
                current = current->getNext();
            }
            std::cout 

        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return first->getData();
        }

        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return last->getData();
        }<< current->getData() << std::endl;
        }
};

#endif