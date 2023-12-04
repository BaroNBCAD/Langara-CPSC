#ifndef STACK_H
#define STACK_H

#include "SinglyLinked.h"


class Stack{
    private:
        LinkedList stack;
    public:
        Stack(){
            stack = LinkedList();
        }
    
        bool IsEmpty(){
            return (stack.IsEmpty());
        }

        void Push(int item){
            stack.AddFirst(item);
            return;
        }

        int Pop(){
            return stack.RemoveFirst();
        }

        int Peek(){
            if (stack.IsEmpty()){
                cout << "List is empty, returning 0!\n";
                return 0;
            }
            return stack.Get(0)->data;
        }

};




#endif