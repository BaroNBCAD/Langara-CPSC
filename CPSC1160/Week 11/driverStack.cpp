#include <iostream>
#include "Stack.h"
using namespace std;


int main(){
    Stack testWithEmptyList;
    if (testWithEmptyList.IsEmpty())
        cout << "list is empty." << endl;
    else
        cout << "list is not empty." << endl;
    cout << "Pop():\n";
    cout << testWithEmptyList.Pop() << endl;
    cout << "Peek():\n";
    cout << testWithEmptyList.Peek() << endl;
    cout << "////////////////" << endl;
    Stack test;
    test.Push(10);
    if (test.IsEmpty())
        cout << "list is empty." << endl;
    else
        cout << "list is not empty." << endl;

    cout << "Peek():\n";
    cout << test.Peek() << endl;
    cout << "Pop():\n";
    cout << test.Pop() << endl;
    cout << "Peek():\n";
    cout << test.Peek() << endl;

    return 0;
}