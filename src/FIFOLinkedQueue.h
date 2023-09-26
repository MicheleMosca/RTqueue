#ifndef FIFOlinkedqueue
#define FIFOlinkedqueue

#include <node.h>
#include <iostream>

#define UNLIMITED -1

template <class T> class FIFOLinkedQueue {  
    private:
        Node<T>* first;
        Node<T>* last;
        int count;
        pthread_cond_t conditionPush;
        pthread_cond_t conditionPop;
        pthread_mutex_t mutex;
        bool blocked;
        int dimension;
    
    public:
        FIFOLinkedQueue(bool blocked = true, int dimension = UNLIMITED){
            first = NULL;
            last = NULL;
            count = 0;
            conditionPush = PTHREAD_COND_INITIALIZER;
            conditionPop = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;

            /* Make the pop function blocked or unblocked */
            this->blocked = blocked;

            this->dimension = dimension;
        }

        void push(T element)
        {
            pthread_mutex_lock(&mutex);

            //if the queue is full => block
            while(this->count == this->dimension){
                pthread_cond_wait(&conditionPop, &mutex);
            }

            Node<T>* tmp = new Node<T>();
            tmp->setData(element);
            tmp->setNext(NULL);

            if (empty()) {
                first = last = tmp;
            }
            else {
                last->setNext(tmp);
                last = tmp;
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
                
            T ret = first->getData();
            Node<T>* tmp = first;
            first = first->getNext();
            count--;
            delete tmp;

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
            std::cout << current->getData() << std::endl;
        }

        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return first->getData();
        }

        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return last->getData();
        }

        int size(void){
            return count;
        }

        bool empty(void){
            return count == 0 ? true : false;
        }
};

#endif