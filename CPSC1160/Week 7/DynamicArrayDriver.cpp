#include <iostream>
#include "DynamicArray.h"
#include <ctime>
using namespace std;


int main(){
    srand(time(0));
    int* a = new int[4];
    a[0] = rand()%50;
    a[1] = rand()%50;
    a[2] = rand()%50;
    a[3] = rand()%50;
    int* b = new int[2];
    b[0] = rand()%50;
    b[1] = rand()%50;
    DynamicArray test(a, 4);
    cout << "Add test:" << endl;
    test.Add(4, b, 2);
    test.Display();
    //////////////////////
    cout << "Remove test:" << endl;
    test.Remove(1, 2);
    test.Display();
    //////////////////////
    cout << "Sort test:" << endl;
    test.Sort(0, 3);
    test.Display();
    //////////////////////
    cout << "operator+ test:" << endl;
    int* c = new int[5];
    c[0] = rand()%50;
    c[1] = rand()%50;
    c[2] = rand()%50;
    c[3] = rand()%50;
    c[4] = rand()%50;
    DynamicArray test2(c, 5);
    test2.Display();
    DynamicArray test3 = test + test2;
    test3.Display();
    //////////////////////
    cout << "operator= test:" << endl;
    test3 = test2;
    test2.Display();
    test3.Display();
    //////////////////////
    cout << "operator+= test:" << endl;
    test3+=test;
    test3.Display();

    delete[] a;
    delete[] b;
    return 0;
}