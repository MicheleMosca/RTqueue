#ifndef MultipleLinkedQueue_H
#define MultipleLinkedQueue_H

#include <iostream>
#include <LinkedQueue.h>
#include <FIFOLinkedQueue.h>
#include <LIFOLinkedQueue.h>

#ifndef queuetype
#define queuetype

enum QueueType { FIFO, LIFO };

#endif

template <class T> class MultipleLinkedQueue {  
    protected:
        LinkedQueue<T> *queue;
        size_t num;
    
    public:
        MultipleLinkedQueue(size_t num, QueueType type, bool blocked = true, int dimension = UNLIMITED){
            this-> num = num;

            switch (type)
            {
                case FIFO:
                    this->queue = new FIFOLinkedQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = FIFOLinkedQueue<T>(blocked, dimension);
                    break;

                case LIFO:
                    this->queue = new LIFOLinkedQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = LIFOLinkedQueue<T>(blocked, dimension);
                    break;
                    
                default:
                    break;
            }
        }

        void push(T element, size_t priority)
        {
            if (priority > this->num)
                throw std::out_of_range("Priority number is greater then number of queue");

            for (size_t i = priority-1; i < this->num; i++)
                if (!this->queue[i].full())
                {
                    this->queue[i].push(element);
                    return;
                }

            this->queue[priority-1].push(element);
        }

        T pop(void)
        {
            for (size_t i = 0; i < this->num; i++)
                if (!this->queue[i].empty())
                    return this->queue[i].pop();

            return this->queue[0].pop();
        }
};

#endif