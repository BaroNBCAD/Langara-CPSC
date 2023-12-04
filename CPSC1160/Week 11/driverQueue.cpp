#include <iostream>
#include "Queue.h"
using namespace std;


int main(){
    Queue testWithEmptyList;
    if (testWithEmptyList.IsEmpty())
        cout << "list is empty." << endl;
    else
        cout << "list is not empty." << endl;
    cout << "Dequeue():\n";
    cout << testWithEmptyList.Dequeue() << endl;
    cout << "PeekRear():\n";
    cout << testWithEmptyList.PeekRear() << endl;
    cout << "PeekFront():\n";
    cout << testWithEmptyList.PeekFront() << endl;
    cout << "////////////////" << endl;

    Queue test;
    test.Enqueue(10);
    test.Enqueue(20);
    if (test.IsEmpty())
        cout << "list is empty." << endl;
    else
        cout << "list is not empty." << endl;

    cout << "PeekFront():\n";
    cout << test.PeekFront() << endl;
    cout << "PeekRear():\n";
    cout << test.PeekRear() << endl;
    cout << "Dequeue():\n";
    cout << test.Dequeue() << endl;
    cout << "PeekFront():\n";
    cout << test.PeekFront() << endl;
    cout << "PeekRear():\n";
    cout << test.PeekRear() << endl;

    return 0;
}