/*
    cre: Danny Oct/7
*/

#ifndef PRIQUE_H
#define PRIQUE_H

#include "SkipList.h"
#include <ctime>

using namespace std;


class PriorityQueue{
    private:
        int maxLevel;
        int size;
        SkipList* skipList;
        bool isEmpty();
        void toDoubleCheck();
public:
    PriorityQueue(int);
    ~PriorityQueue();
    void Enqueue();
    int Dequeue();
    void Process();
};

#endif