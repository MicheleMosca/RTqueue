#include <FIFOqueue.h>
#include <iostream>

int main()
{
    FIFOQueue<int>* queue = new FIFOQueue<int>();

    queue->push(1);
    queue->push(2);
    queue->push(3);

    std::cout << "Values:\n";

    std::cout << queue->pop() << "\n";
    std::cout << queue->pop() << "\n";
    std::cout << queue->pop() << "\n";
    std::cout << queue->pop() << "\n";
}