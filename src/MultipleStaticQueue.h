#ifndef MultipleStaticQueue_H
#define MultipleStaticQueue_H

#include <iostream>
#include <StaticQueue.h>
#include <FIFOStaticQueue.h>
#include <LIFOStaticQueue.h>

#ifndef queuetype
#define queuetype

enum QueueType { FIFO, LIFO };

#endif

template <class T> class MultipleStaticQueue {  
    protected:
        StaticQueue<T> *queue;
        size_t num;
    
    public:
        MultipleStaticQueue(size_t num, QueueType type, size_t dimension, bool blocked = true){
            this-> num = num;

            switch (type)
            {
                case FIFO:
                    this->queue = new FIFOStaticQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = FIFOStaticQueue<T>(dimension, blocked);
                    break;

                case LIFO:
                    this->queue = new LIFOStaticQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = LIFOStaticQueue<T>(dimension, blocked);
                    break;
                    
                default:
                    break;
            }
        }

        void push(T element, size_t priority = 0)
        {
            if (priority >= this->num)
                throw std::out_of_range("Priority number is greater then number of queue");

            for (size_t i = priority; i < this->num; i++)
                if (!this->queue[i].full())
                {
                    this->queue[i].push(element);
                    return;
                }

            this->queue[priority].push(element);
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