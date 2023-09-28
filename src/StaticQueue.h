#ifndef staticqueue
#define staticqueue

template <class T> class StaticQueue {  
    protected:
        T *queue;
        size_t firstElem;
        size_t lastElem;
        size_t dimension;
    
    public:
        StaticQueue(size_t dimension){
            this->dimension = dimension;
            queue = new T[this->dimension];
            this->firstElem = this->lastElem = 0;
        }

        virtual void push(T element) = 0;

        virtual T pop(void) = 0;

        T front(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return this->queue[this->firstElem];
        }

        T back(void){
            if (empty())
                throw std::logic_error("Queue is empty");
            return this->queue[this->lastElem];
        }

        int size(void){
            return this->dimension;
        }

        bool empty(void){
            return this->firstElem == this->lastElem ? true : false;
        }

};

#endif