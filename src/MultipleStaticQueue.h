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

//! Stucture definition of a MultipleStaticQueue

template <class T> class MultipleStaticQueue {  
    protected:
        //! Pointer to the StaticQueue
        StaticQueue<T> *queue;

        //! Number of the queues
        size_t num;
    
    public:
        //! Constructor of the MultipleStaticQueue
        MultipleStaticQueue(size_t num, QueueType type, size_t dimension, bool blocked = true, bool persistence = true){
            this-> num = num;

            //! switch case for FIFO or LIFO politics
            switch (type)
            {
                case FIFO:
                    this->queue = new FIFOStaticQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = FIFOStaticQueue<T>(dimension, blocked, persistence);
                    break;

                case LIFO:
                    this->queue = new LIFOStaticQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = LIFOStaticQueue<T>(dimension, blocked, persistence);
                    break;
                    
                default:
                    break;
            }
        }

        //! push method for each queue
        void push(T element, size_t priority = 0)
        {
            //! Check priority value
            if (priority >= this->num)
                throw std::out_of_range("Priority number is greater then number of queue");

            //! Insert element
            for (size_t i = priority; i < this->num; i++)
                if (!this->queue[i].full() || !this->queue[i].persistent())
                {
                    this->queue[i].push(element);
                    return;
                }

            this->queue[priority].push(element);
        }

        //! pop method for each queue
        T pop(void)
        {
            for (size_t i = 0; i < this->num; i++)
                if (!this->queue[i].empty())
                    return this->queue[i].pop();

            return this->queue[0].pop();
        }
};

#endif