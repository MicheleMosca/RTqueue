#include <RTqueue.h>
#include <iostream>

int main()
{
    FIFOLinkedQueue<int>* queue = new FIFOLinkedQueue<int>();

    queue->push(1);
    queue->push(2);
    queue->push(3);

    std::cout << "Values:\n";

    std::cout << queue->pop() << "\n";
    std::cout << queue->pop() << "\n";
    std::cout << queue->pop() << "\n";
    std::cout << queue->pop() << "\n";
}