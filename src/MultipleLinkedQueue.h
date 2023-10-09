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

//! Structure definition of a MultipleLinkedQueue

template <class T> class MultipleLinkedQueue {
    protected:
        //! Pointer to the LinkedQueue
        LinkedQueue<T> *queue;

        //! Number of the queues
        size_t num;
    
    public:
        //! Constructor of the MultipleLinkedQueue
        MultipleLinkedQueue(size_t num, QueueType type, int dimension = UNLIMITED, bool blocked = true, bool persistence = true){
            this-> num = num;

            //! switch case for FIFO or LIFO politics
            switch (type)
            {
                case FIFO:
                    this->queue = new FIFOLinkedQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = FIFOLinkedQueue<T>(dimension, blocked, persistence);
                    break;

                case LIFO:
                    this->queue = new LIFOLinkedQueue<T>[this->num];
                    for (size_t i = 0; i < this->num; i++)
                        this->queue[i] = LIFOLinkedQueue<T>(dimension, blocked, persistence);
                    break;
                    
                default:
                    break;
            }
        }

        //! push method for each queue
        void push(T element, size_t priority)
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

        //! pop mehod for each queue
        T pop(void)
        {
            for (size_t i = 0; i < this->num; i++)
                if (!this->queue[i].empty())
                    return this->queue[i].pop();

            return this->queue[0].pop();
        }
};

#endif