#ifndef FIFOstaticqueue
#define FIFOstaticqueue

#include <node.h>
#include <iostream>

template <class T> class FIFOStaticQueue : public StaticQueue<T> {  
    
    public:
        FIFOStaticQueue(size_t dimension) : StaticQueue<T>(dimension){}

        void push(T element)
        {
            this->queue[this->lastElem] = element;
            this->lastElem++;
        }

        T pop(void){
            if ( this->empty() ){
                throw std::logic_error("Queue is empty");
            }
                
            this->firstElem++;
            return this->queue[this->firstElem -1];
        }

        void printQueue(){
            if ( this->empty() ){
                throw std::logic_error("Queue is empty");
            }
        }
};

#endif