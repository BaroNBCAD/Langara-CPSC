#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>
using namespace std;
class Stack{
private:
    vector<int> data;
    int size;
public:
    /**
     * Default constructor. Initializes the size to 0.
     *
     * @param none
     * 
     * @return a Stack object.
     * 
     * @complexity O(1) in the worst case.
     */
    Stack(){
        size = 0;
    }

    /**
     * Removes the last element from the stack and returns it. If the stack is empty, outputs a message to the console and returns 0.
     *
     * @param none
     * 
     * @return integer, the element removed.
     * 
     * @complexity O(1) on average, O(n) worst case where n is the number of elements in the stack (rare).
     */
    int Pop(){
        if(size == 0){
            cout << "stack is empty! returning 0." << endl;
            return 0;
        }
        int temp = data.back(); // O(1)
        data.pop_back(); // O(1) on average, O(n) worst case 
        size--; // O(1)
        return temp;
    }
    
    /**
     * Adds an element to the top of the stack.
     *
     * @param integer, the element to be added.
     * 
     * @return none
     * 
     * @complexity O(1) on average, O(n) worst case where n is the number of elements in the stack (rare).
     */
    void Push(int x){
        data.push_back(x); // O(1) on average, O(n) worst case 
        size++; // O(1)
    }

    /**
     * Returns the element at the top of the stack. If the stack is empty, outputs a message to the console and returns 0.
     *
     * @param none
     * 
     * @return integer, the element at the top of the stack.
     * 
     * @complexity O(1) in the worst case.
     */
    int Peek(){
        if(size == 0){
            cout << "stack is empty! returning 0." << endl;
            return 0;
        }
        return data.back();
    }    
    

};

#endif