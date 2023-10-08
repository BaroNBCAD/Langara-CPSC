/*
    cre: Danny Oct/7
    Source: using SkipList from Muntaseer
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include "Node.h"


#ifndef SKIPLIST_H
#define SKIPLIST_H

using namespace std;

class SkipList{
public:
    // Maximum allowed level index
    int MAXIMUM_ALLOWED_LEVEL_INDEX;
 
    // current maximum level amongst the inserted nodes
    int currentHighestLevelIndex;
    
    // the head node's next links are connected to the first node at every level
    Node *head;
    Node* tail; // last node at every level

    SkipList(int maxLevels){
        MAXIMUM_ALLOWED_LEVEL_INDEX = maxLevels;

        // initially we have the bottom-most level only
        currentHighestLevelIndex = 0;
    
        // create the header node, value is irrelevant (as long as it doesn't match an inserted value - NO REPEATS), number of next links is important (initially this node is the first node at every level)
        head = new Node(INT_MIN, MAXIMUM_ALLOWED_LEVEL_INDEX);
        tail = new Node(INT_MAX, MAXIMUM_ALLOWED_LEVEL_INDEX); // last nodes at each level
        // connect head to tail at every level
        for(int i = 0; i <= MAXIMUM_ALLOWED_LEVEL_INDEX; i++){
            head->next[i] = tail; // head's prev is null
            tail->prev[i] = head; // tail's next is null
        }
    }

    Node* CreateNode(int value, int pri){
        // create a new node with next links for every level that this node will be part of
        // it will use these links to connect to the next node at each level  
        return new Node(value, pri);
    }

    void InsertElement(int value, int priority){
        Node* n = CreateNode(value, priority);
        if (priority > currentHighestLevelIndex){
            currentHighestLevelIndex = priority;
        }
        for (int i = 0; i<=priority; i++){
            n->next[i] = tail;
            n->prev[i] = tail->prev[i];
            tail->prev[i]->next[i] = n;
            tail->prev[i] = n;
        }
    }

    int Delete(){  //or, Dequeue()
        if (head->next[currentHighestLevelIndex] == tail) //List is empty, but this case is not gonna occur
            return INT_MIN;

        Node* toDelete = head->next[currentHighestLevelIndex];
        for (int i = 0; i<=currentHighestLevelIndex; i++){
            toDelete->prev[i]->next[i] = toDelete->next[i];
            toDelete->next[i]->prev[i] = toDelete->prev[i];
            toDelete->prev[i] = nullptr;
            toDelete->next[i] = nullptr;
        }
        int dataToReturn = toDelete->value;
        delete toDelete;
        while (currentHighestLevelIndex > 0 && head->next[currentHighestLevelIndex] == tail){
                currentHighestLevelIndex--;
        }
        return dataToReturn;
    }

    bool Search(int value){
        /*
            From Danny: Since there's no use of this, you can do whatever you want here.
        */
       return false;
    }

    void ShowForward(){
        cout << "Showing forward:\n";
        Node *node = head->next[currentHighestLevelIndex];
        if (node == tail) return;
        for (int i = currentHighestLevelIndex; i >= 0;i--){
            node = head->next[i];
            cout << "Level " << i << ": ";
            while (node != nullptr && node->next[i] != tail){
                cout << node->value << " -> ";
                node = node->next[i];
            }
            if(node){
                cout << node->value << " .\n";
            }
            else{
                cout << " .\n";
            }
        }
    }

    void ShowBackward(){
        cout << "Showing backward:\n";
        Node *node = head->next[currentHighestLevelIndex];
        if (node == tail) return;
        for (int i = currentHighestLevelIndex; i >= 0;i--){
            Node *node = tail->prev[i];
            cout << "Level " << i << ": ";
            while (node != nullptr && node->prev[i] != head){
                cout << node->value << " -> ";
                node = node->prev[i];
            }
            if(node){
                cout << node->value << " .\n";
            }
            else{
                cout << " .\n";
            }
        }
    }
};

#endif