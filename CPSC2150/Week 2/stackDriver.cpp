#include "Stack.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){

   Stack s;

    s.Peek();
    s.Push(123);
    s.Push(45);

    cout << s.Peek() << endl;
    cout << s.Pop() << " popped." << endl;
    cout << s.Peek() << endl;
    return 0;
}