#include <node.h>
#include <iostream>

int main()
{
    Node<int>* node = new Node<int>();
    node->setData(1);
    std::cout << "Value: " << node->getData() << "\n";
}