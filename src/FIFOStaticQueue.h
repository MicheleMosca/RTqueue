#ifndef FIFOstaticqueue
#define FIFOstaticqueue

#include <node.h>
#include <iostream>

template <class T> class FIFOStaticQueue {  
    private:
        T queue[];
        T *firstElem;
        T *lastElem;
        size_t dimension;
    
    public:
        FIFOQueue(size_t dimension){
            this->dimension = dimension;
            queue = new T[this->dimension];
        }

        void push(T element)
        {
            Node<T>* tmp = new Node<T>();
            tmp->setData(element);
            tmp->setNext(NULL);

            if (isEmpty()) {
                first = last = tmp;
            }
            else {
                last->setNext(tmp);
                last = tmp;
            }
            count++;
        }

        T pop(void){
            if ( empty() ){
                throw std::logic_error("Queue is empty");
            }
                
            T ret = first->getData();
            Node<T>* tmp = first;
            first = first->getNext();
            count--;
            delete tmp;
            return ret;
        }

        void printQueue(){
            if ( empty() ){
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

        T first(void){
            if ( empty() ){
                throw std::logic_error("Queue is empty");
            }
            return this.queue[this->firstElem];
        }

        T last(void){
            if ( empty() ){
                throw std::logic_error("Queue is empty");
            }
            return this.queue[this->lastElem];
        }

        int size(void){
            return this->dimension;
        }

        bool empty(void){
            return this->firstElem == this->lastElem ? true : false;
        }
};

#endif