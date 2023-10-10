#include <iostream>
#include <RTqueue.h>
#include <cassert>

using namespace std;

#define assertm(exp, msg) assert(((void)msg, exp))

int main(){
    //! Test FIFOLinkedQueue
    //! dimension: 3
    //! blocked: true
    //! persistance: false
    cout << "[*] Executing tests of peristence with FIFOLinkedQueue of dimension 3 and push these values (with a pop after 5 element pushed):" << endl;
    cout << "[*] 1,2,3,4,5,6,7,8,9" << endl;
    cout << "[*] Expected pop values:" << endl;
    cout << "[*] 7,8,9" << endl << endl;
    
    LinkedQueue<int> *queueLinked;

    cout << "[*] Test" << endl;
    
    queueLinked = new FIFOLinkedQueue<int>(3, true, false);
    
    //! push five elements
    for (size_t i = 1; i <= 5; i++)
        queueLinked->push(i);
    
    //! assert test: expected pop value = 3
    cout << "assert test: expected pop value = 3 ... ";
    assertm(queueLinked->pop() == 3, "Expected pop value 3");
    cout << "[ OK ]" << endl;

    //! push another five elements
    for (size_t i = 6; i <= 9; i++)
        queueLinked->push(i);

    //! pop
    cout << "final pop values: ";
    while (!queueLinked->empty())
    {
        cout << queueLinked->pop() << " ";
    }
    cout << endl;

    cout << endl;
    cout << "----- END TEST -----" << endl;
    cout << endl;


    //! Test FIFOStaticQueue
    //! dimension: 3
    //! blocked: true
    //! persistance: false
    cout << "[*] Executing tests of peristence with FIFOStaticQueue of dimension 3 and push these values (with a pop after 5 element pushed):" << endl;
    cout << "[*] 1,2,3,4,5,6,7,8,9" << endl;
    cout << "[*] Expected pop values:" << endl;
    cout << "[*] 7,8,9" << endl << endl;

    StaticQueue<int> *queueStatic;

    cout << "[*] Test" << endl;

    queueStatic = new FIFOStaticQueue<int>(3, true, false);
    
    //! push five elements
    for (size_t i = 1; i <= 5; i++)
        queueStatic->push(i);
    
    //! assert test: expected pop value = 3
    cout << "assert test: expected pop value = 3 ... ";
    assertm(queueStatic->pop() == 3, "Expected pop value 3");
    cout << "[ OK ]" << endl;

    //! push another five elements
    for (size_t i = 6; i <= 9; i++)
        queueStatic->push(i);

    //! pop
    cout << "final pop values: ";
    while (!queueStatic->empty())
    {
        cout << queueStatic->pop() << " ";
    }
    cout << endl;

    cout << endl;
    cout << "----- END TEST -----" << endl;
    cout << endl;


    //! Test FIFOLinkedQueue
    //! dimension: 1
    //! blocked: false
    //! persistance: true
    cout << "[*] Executing tests of unblocked push and pop with FIFOLinkedQueue of dimension 1 and push these values:" << endl;
    cout << "[*] 1,2" << endl;
    cout << "[*] Expected pop value: 1" << endl << endl;
    
    queueLinked = new FIFOLinkedQueue<int>(1, false, true);

    cout << "[*] Test" << endl;
    
    bool test_passed = true;

    //! try to push two element
    cout << "Trying to overflow the queue ... ";
    try
    {
        for (size_t i = 1; i <= 2; i++)
            queueLinked->push(i);

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[ OK ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is full");

    //! try to pop element in a empty queue
    cout << "Trying to pop in a empty queue ... ";
    try
    {
        for (size_t i = 1; i <= 2; i++)
            queueLinked->pop();

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[ OK ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is empty");

    cout << endl;
    cout << "----- END TEST -----" << endl;
    cout << endl;


    //! Test FIFOStaticQueue
    //! dimension: 1
    //! blocked: false
    //! persistance: true
    cout << "[*] Executing tests of unblocked push and pop with FIFOStaticQueue of dimension 1 and push these values:" << endl;
    cout << "[*] 1,2" << endl;
    cout << "[*] Expected pop value: 1" << endl << endl;

    queueStatic = new FIFOStaticQueue<int>(1, false, true);

    cout << "[*] Test" << endl;
    
    test_passed = true;

    //! try to push two element
    cout << "Trying to overflow the queue ... ";
    try
    {
        for (size_t i = 1; i <= 2; i++)
            queueStatic->push(i);

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[ OK ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is full");
    
    //! try to pop element in a empty queue
    cout << "Trying to pop in a empty queue ... ";
    try
    {
        for (size_t i = 1; i <= 2; i++)
            queueStatic->pop();

        test_passed = false;
    }
    catch(const std::logic_error& e)
    {
        test_passed = true;
        cout << "[ OK ]" << endl;
    }
    assertm(test_passed == true, "Expected logic_error because the queue is empty");

    cout << endl;
    cout << "----- END TEST -----" << endl;
    cout << endl;


    //! Test FIFOLinkedQueue
    //! dimension: 2
    //! blocked: false
    //! persistance: false
    cout << "[*] Executing tests of unblocked push and pop with FIFOLinkedQueue of dimension 2 and push these values:" << endl;
    cout << "[*] 1,2,3,4" << endl;
    cout << "[*] Expected pop value: 3,4" << endl << endl;

    FIFOLinkedQueue<int> *linkedQueue = new FIFOLinkedQueue<int>(2,false, false);
    
    //! push four elements
    for(size_t i = 1; i <= 4; i++)
        linkedQueue->push(i);
    
    //! pop
    cout << "final pop values: ";
    while (!linkedQueue->empty())
        cout << linkedQueue->pop() << " ";
    cout << endl;

    cout << endl;
    cout << "----- END TEST -----" << endl;
    cout << endl;

    return 0;
}
