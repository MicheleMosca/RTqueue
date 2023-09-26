#ifndef FIFOlinkedqueue
#define FIFOlinkedqueue

#include <node.h>
#include <iostream>

template <class T> class FIFOLinkedQueue {  
    private:
        Node<T>* first;
        Node<T>* last;
        int count;
        pthread_cond_t condition;
        pthread_mutex_t mutex;
        bool blocked;
    
    public:
        FIFOLinkedQueue(bool blocked = true){
            first = NULL;
            last = NULL;
            count = 0;
            condition = PTHREAD_COND_INITIALIZER;
            mutex = PTHREAD_MUTEX_INITIALIZER;

            /* Make the pop function blocked or unblocked */
            this->blocked = blocked;
        }

        void push(T element)
        {
            pthread_mutex_lock(&mutex);

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

            pthread_cond_signal(&condition);

            pthread_mutex_unlock(&mutex);
        }

        T pop(void){
            pthread_mutex_lock(&mutex);

            /* release function if the queue is empty and unblocked function is enable */
            if ( empty() && !blocked ){
                pthread_mutex_unlock(&mutex);
                throw std::logic_error("Queue is empty");
            }

            if (empty()){
                pthread_cond_wait(&condition, &mutex);
            }
                
            T ret = first->getData();
            Node<T>* tmp = first;
            first = first->getNext();
            count--;
            delete tmp;

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