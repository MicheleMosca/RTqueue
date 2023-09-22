#ifndef FIFOqueue
#define FIFOqueue

#include <node.h>
#include <iostream>

template <class T> class FIFOQueue {  
    private:
        Node<T>* first;
        Node<T>* last;
        int count;
    
    public:
        FIFOQueue(void){
            first = NULL;
            last = NULL;
            count = 0;
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
            if ( isEmpty() ){
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
            if(isEmpty()){
                std::cout << "Queue is empty" << std::endl;
                return;
            }

            //prendo la coda da stampare e la itero
            Node<T>* current = first;
            while (current->getNext()) {
                std::cout << current->getData() << ' ';
                current = current->getNext();
            }
            std::cout << current->getData() << std::endl;
        }

        T First(void){
            if (isEmpty())
                std::cout << "Queue is empty" << std::endl;
            return first->getData();
        }

        T Last(void){
            if (isEmpty())
                std::cout << "Queue is empty" << std::endl;
            return last->getData();
        }

        int Size(void){
            return count;
        }

        bool isEmpty(void){
            return count == 0 ? true : false;
        }
};

#endif