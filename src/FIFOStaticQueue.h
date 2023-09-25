#ifndef FIFOstaticqueue
#define FIFOstaticqueue

#include <node.h>
#include <iostream>

template <class T> class FIFOStaticQueue {  
    private:
        T queue[];
        size_t firstElem;
        size_t lastElem;
        size_t dimension;
    
    public:
        FIFOStaticQueue(size_t dimension){
            this->dimension = dimension;
            queue = new T[this->dimension];
            this->firstElem = this->lastElem = 0;
        }

        void push(T element)
        {
            this.queue[this->lastElem] = element;
            this->lastElem++;
        }

        T pop(void){
            if ( empty() ){
                throw std::logic_error("Queue is empty");
            }
                
            this->firstElem++;
            return this.queue[this->firstElem -1];
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