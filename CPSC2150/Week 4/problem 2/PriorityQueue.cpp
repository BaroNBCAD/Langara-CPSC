/*
    cre: Danny Oct/7
*/

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int lv){
    maxLevel = lv;
    size = 0;
    skipList = new SkipList(maxLevel);
}

bool PriorityQueue::isEmpty(){
    return size==0;
}

void PriorityQueue::Enqueue(){
    int data = rand()%100+1;
    int priority = rand()%(skipList->MAXIMUM_ALLOWED_LEVEL_INDEX);
    skipList->InsertElement(data, priority);
    size++;
    return;
}

int PriorityQueue::Dequeue(){
    if (isEmpty()){
        cout << "There's no node to dequeue" << endl;
        return INT_MIN;
    }
    size--;
    return skipList->Delete();
}

void PriorityQueue::toDoubleCheck(){
    cout << "-------------------" << endl;
    skipList->ShowForward();
    skipList->ShowBackward();
    cout << "-------------------" << endl;
}

void PriorityQueue::Process(){
    toDoubleCheck();
    if (isEmpty()){
        cout << "The Queue is empty" << endl;
        return;
    }
    cout << "Data(s): ";
    while (size>1){
        int dataRetrieve = Dequeue();
        cout << dataRetrieve << " -> ";
    }
    int dataRetrieve = Dequeue();
    cout << dataRetrieve << ".";
    return;
}

PriorityQueue::~PriorityQueue(){
    delete skipList;
}
