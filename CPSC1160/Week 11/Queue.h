#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinked.h"


class Queue{
    private:
        LinkedList queue;
    public:
        Queue(){
            queue = LinkedList();
        }
    
        bool IsEmpty(){
            return (queue.IsEmpty());
        }

        void Enqueue(int item){
            queue.AddNodeLast(item);
            return;
        }

        int Dequeue(){
            return queue.RemoveFirst();
        }

        int PeekFront(){
            if (queue.IsEmpty()){
                cout << "List is empty, returning 0!\n";
                return 0;
            }
            return queue.Get(0)->data;
        }

        int PeekRear(){
            if (queue.IsEmpty()){
                cout << "List is empty, returning 0!\n";
                return 0;
            }
            return queue.GetLast()->data;
        }

};




#endif