#include <iostream>
#include <RTqueue.h>
#include <cassert>

using namespace std;

int main()
{
    cout << "[*] Executing tests of peristence with queue of dimension 3 and push these values (with a pop after 5 element pushed):" << endl;
    cout << "[*] 1,2,3,4,5,6,7,8,9" << endl;
    cout << "[*] Expected pop values:" << endl;
    cout << "[*] 7,8,9" << endl << endl;
    
    LinkedQueue<int> *queueLinked;

    cout << "[*] Test with FIFOLinkedQueue" << endl;
    queueLinked = new FIFOLinkedQueue<int>(3, true, false);
    for (size_t i = 1; i <= 5; i++)
        queueLinked->push(i);
    assert(queueLinked->pop() == 3);
    for (size_t i = 6; i <= 9; i++)
        queueLinked->push(i);
    while (!queueLinked->empty())
    {
        cout << queueLinked->pop() << " ";
    }
    cout << endl;
    

    return 0;
}