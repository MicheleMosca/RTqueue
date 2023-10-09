#include <iostream>
#include <RTqueue.h>
#include <cassert>

using namespace std;

#define assertm(exp, msg) assert(((void)msg, exp))

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
    assertm(queueLinked->pop() == 3, "Expected pop value 3");
    for (size_t i = 6; i <= 9; i++)
        queueLinked->push(i);
    while (!queueLinked->empty())
    {
        cout << queueLinked->pop() << " ";
    }
    cout << endl;


    StaticQueue<int> *queueStatic;
    cout << "[*] Test with FIFOStaticQueue" << endl;
    queueStatic = new FIFOStaticQueue<int>(3, true, false);
    for (size_t i = 1; i <= 5; i++)
        queueStatic->push(i);
    assertm(queueStatic->pop() == 3, "Expected pop value 3");
    for (size_t i = 6; i <= 9; i++)
        queueStatic->push(i);
    while (!queueStatic->empty())
    {
        cout << queueStatic->pop() << " ";
    }
    cout << endl;
    

    cout << "[*] Executing tests of unblocked push and pop with queue of dimension 1 and push these values:" << endl;
    cout << "[*] 1,2" << endl;
    cout << "[*] Expected pop values:" << endl;
    cout << "[*] 1" << endl << endl;

    cout << "[*] Test with FIFOLinkedQueue" << endl;
    queueLinked = new FIFOLinkedQueue<int>(1, false, true);
    bool test_passed = true;

    try
    {
        for (size_t i = 1; i <= 2; i++)
            queueLinked->push(i);

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[*] Test on queue is full exception: [ ok ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is full");
    
    try
    {
        for (size_t i = 1; i <= 2; i++)
            cout << queueLinked->pop() << endl;

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[*] Test on queue is empty exception: [ ok ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is empty");

    cout << endl;


    cout << "[*] Test with FIFOStaticQueue" << endl;
    queueStatic = new FIFOStaticQueue<int>(1, false, true);
    test_passed = true;

    try
    {
        for (size_t i = 1; i <= 2; i++)
            queueStatic->push(i);

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[*] Test on queue is full exception: [ ok ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is full");
    
    try
    {
        for (size_t i = 1; i <= 2; i++)
            cout << queueStatic->pop() << endl;

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[*] Test on queue is empty exception: [ ok ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is empty");

    cout << endl;


    return 0;
}