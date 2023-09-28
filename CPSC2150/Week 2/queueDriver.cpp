#include "Queue.h"
#include <iostream>
using namespace std;
int main()
{

    Queue q;

    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);

    cout << "PeekFront: " << q.PeekFront() << endl;
    cout << "PeekRear: " << q.PeekRear() << endl;

    cout << "Dequeue: " << q.Dequeue() << endl;

    cout << "PeekFront: " << q.PeekFront() << endl;
    cout << "PeekRear: " << q.PeekRear() << endl;

    q.Enqueue(4);

    q.Show();

    cout << "PeekFront: " << q.PeekFront() << endl;
    cout << "PeekRear: " << q.PeekRear() << endl;

    // // LinkedList test
    // LinkedList<string> myList;
    // myList.add(0, "orange");
    // myList.add(1, "apple");
    // myList.add(2, "mango");

    // cout << "Original List: ";
    // myList.Show();

    // myList.removeLast();

    // cout << "After removeLast(): ";
    // myList.Show();

    // myList.add(1, "blueberry");

    // cout << "After add(1, \"blueberry\"): ";
    // myList.Show();

    // cout << "Contains apple? " << myList.contains("apple") << endl;
    // cout << "Contains banana? " << myList.contains("banana") << endl;

    // myList.clear();

    // cout << "After clear(): ";
    // myList.Show();

    return 0;
}
