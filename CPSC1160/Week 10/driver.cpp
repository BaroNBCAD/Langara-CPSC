/*
    Danny
*/

#include <iostream>
#include "SinglyLinked.h"
using namespace std;

int main(){

    LinkedList* test = new LinkedList(5);
    cout << "Display original linked list:" << endl;
    test->Display();

    //RemoveFirst:
    cout << "RemoveFirst test" << endl;
    test->RemoveFirst();
    test->Display();

    //AddFirst:
    cout << "AddFirst test"<<endl;
    test->AddFirst(0);
    test->Display();

    //Get(int i)
    cout << "Get(int i) test" << endl;
    int i = 1;
    Node* testGetIntI = test->Get(i);
    if (testGetIntI){
        cout << "Value at index [" << i << "] is: " << testGetIntI->data << endl;
    }
    else{
        cout << "Index [i] is invalid." << endl;
    }

    //CopyConstructor
    cout << "CopyConstructor test" << endl;
    LinkedList copyTest(*test);
    copyTest.Display();
    cout << "test head address: " << test->Get(0) << endl;
    cout << "copyTest head address: " << copyTest.Get(0) << endl;

    //Swap
    cout << "Swap test" << endl;
    cout << "test content: ";
    test->Display();
    test->Swap(3, 1);
    test->Display();

    //Split
    cout << "Split test" << endl;
    int n = 2;
    unsigned int* splitIndices = new unsigned int[n];
    splitIndices[0] = 1;
    splitIndices[1] = 2;
    cout << "Display original linked list:" << endl;
    test->Display();
    LinkedList* result = test->Split(splitIndices, n);
    if (result){
        for (int i = 0; i < n+1; i++){
            cout << "List [i]: " << i << endl;
            result[i].Display();
        }
    }
    else
        cout << "result is nullptr." << endl;

    delete[] result;
    //test now is empty

    // Sorting
    cout << "Sorting test" << endl;
    cout << "Before: " << endl;
    copyTest.Swap(3, 1);
    copyTest.Swap(2, 4);
    copyTest.Display();
    copyTest.InsertionSortList();
    cout << "After:" << endl;
    copyTest.Display();

    // operator=
    cout << "operator= test" <<endl;
    *test = copyTest;
    test->Display();

    // operator+
    cout << "operator+ test" << endl;
    LinkedList* testPlus = *test + copyTest;
    testPlus->Display();
    if (testPlus)
        delete testPlus;

    // operator +=
    cout << "operator+= test" <<endl;
    LinkedList* operatorPlusEqualTest = new LinkedList(2);
    cout << "operatorPlusEqualTest content: ";
    operatorPlusEqualTest->Display();
    cout << "test content: ";
    test->Display();
    cout << "*test += *operatorPlusEqualTest: ";
    *test += *operatorPlusEqualTest;
    test->Display();
    if (operatorPlusEqualTest)
        delete operatorPlusEqualTest;

    // operator-
    cout << "operator- test" << endl;
    copyTest.RemoveLast();
    copyTest.RemoveLast();
    copyTest.AddNodeLast(100);
    copyTest.AddNodeLast(200);
    copyTest.AddNodeLast(3);
    copyTest.AddNodeLast(4);
    cout << "copyTest content: ";
    copyTest.Display();
    cout << "test content: ";
    test->Display();
    LinkedList* testMinus = copyTest - *test;
    cout << "copyTest - test: ";
    testMinus->Display();
    if (testMinus)
        delete testMinus;

    cout << "test - copyTest: ";
    testMinus = *test - copyTest;
    testMinus->Display();
    if (testMinus)
        delete testMinus;

    // operator<<
    cout << "operator<< test"<<endl;
    cout << *test << endl;

    // operator>>
    cout << "operator>> test"<<endl;
    cin >> *test;
    cout << *test;
    
    delete test;
    return 0;
}