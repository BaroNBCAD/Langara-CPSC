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

    ~SkipList(){
        while (head->next[0] != tail){
            Node* toDel = head->next[0];
            head->next[0] = toDel->next[0];

            delete toDel;
            toDel = nullptr;
        }

        delete head;
        head = nullptr;
        delete tail;
        tail = nullptr;
    }

    int RandomLevel(){
        float probablity = (float)rand()/RAND_MAX; // flip a coin
        int lvl = 0;
        while (probablity < 0.5 && lvl < MAXIMUM_ALLOWED_LEVEL_INDEX){
            lvl++; // landed heads so increase level by 1
            probablity = (float)rand()/RAND_MAX; // flip a coin again
        }
        return lvl;        
    }

    Node* CreateNode(int value, int level){
        // create a new node with next links for every level that this node will be part of
        // it will use these links to connect to the next node at each level  
        return new Node(value, level);
    }

    void InsertElement(int value){
        Node *current = head; // start at head node
        vector<Node*> update(MAXIMUM_ALLOWED_LEVEL_INDEX+1, nullptr); // this will hold the nodes that need updating at every level after the insert takes place
        for (int i = currentHighestLevelIndex; i >= 0; i--){ // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be inserted here then find out where (i.e. after which node)
            while (current->next[i] != nullptr && current->next[i]->value < value){
                current = current->next[i];
            }
            // found the node after which the value is to be placed at level i
            update[i] = current;
            // move down a level, if possible 
        }    
        
        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to the right where the value is to be inserted to see if the value already exists there (NO REPEATS allowed)
        current = current->next[0];
    
        if (current == nullptr || current->value != value){
            int ranLevel = RandomLevel(); // choose a random level upto where the new node will be placed (starting from level 0)
    
            if (ranLevel > currentHighestLevelIndex){
                // if random level for current node is higher than the current maximum level for existing nodes; then set head as the node after which the new value is to be inserted for each level over current maximum to the level chosen for new value to be inserted (update currently contains nulls for these level(s)).
                for (int i = currentHighestLevelIndex+1; i <= ranLevel; i++){
                    update[i] = head;
                }
    
                // also change the current maximum level for the existing nodes
                currentHighestLevelIndex = ranLevel;
            }
    
            // create new node with next links for every level from ranLevel to zero
            Node* n = CreateNode(value, ranLevel);
    
            // placing new node in the correct place at every level
            for (int i = 0; i<=ranLevel; i++){
                // n connects as a new node between update[i] and update[i]->next[i]
                n->next[i] = update[i]->next[i];
                n->prev[i] = update[i];
                // update[i] connects to n (update[i] is the node before n)
                update[i]->next[i] = n;
                // n->next[i] (this was originally update[i]->next[i], the node that should be after n) connects back to n
                n->next[i]->prev[i] = n;
            }
        }           
    }

    void Delete(int value){
        // remove value from skip list (all levels) if it exists (output a message if it does not exist)
        Node *current = head; // start at head node
        vector<Node*> update(MAXIMUM_ALLOWED_LEVEL_INDEX+1, nullptr); // this will hold the nodes that need updating at every level after the delete takes place
        for (int i = currentHighestLevelIndex; i >= 0; i--){ // start at the highest level and move down so that more nodes may be skipped
            // for level i, if value is to be deleted from here then find out where from (i.e. after which node could it be)
            while (current->next[i] != nullptr && current->next[i]->value < value){
                current = current->next[i]; // moving right on level i
            }
            if(current->next[i] != nullptr && current->next[i]->value == value){
                // found the node after which exists the target node (node that is to be deleted from level i)
                update[i] = current;
            }
            
            // move down a level, if possible 
        }

        // at level 0, where current is pointing to by the end of the preceding loop, move over one node to the right to see value exists there before we try to delete it
        current = current->next[0];
    
        if (current != nullptr && current->value == value){
            // value exists at level 0, so delete it from all levels where it is located. 
            for (int i = 0; i <= currentHighestLevelIndex; i++){
                if(update[i]){ // first we ensure that value exists at level i (otherwise update[i] will be null)
                    // update[i] connects to the node after current (current->next[i])
                    update[i]->next[i] = current->next[i];
                    // current->next[i] (the node that should be after update[i]) connects back to update[i]
                    current->next[i]->prev[i] = update[i];
                    // disconnect current from level i - are these necessary?
                    current->next[i] = nullptr;
                    current->prev[i] = nullptr;
                }
            }
            // delete current
            delete current;
            // update currentHighestLevelIndex if necessary
            while (currentHighestLevelIndex >= 0 && head->next[currentHighestLevelIndex] == tail){
                currentHighestLevelIndex--;
            }
        }
        else{
            // if update[0] is nullptr then preceding loop was unable to find value at level 0
            cout << "Value " << value << " does not exist in the skip list.\n";
        }
    }

    bool Search(int value){
        // TO BE COMPLETED
        // search for value in skip list and return true if it exists; false otherwise

        Node *current = head; // start at head node
        for (int i = currentHighestLevelIndex; i >= 0; i--){ // start at the highest level and move down so that more nodes may be skipped
            // for level i, keep moving right while values are less than what we are looking for (and if it is possible to move any further right
            while (current->next[i] != nullptr && current->next[i]->value < value){
                current = current->next[i]; // moving right
            }
            if(current->next[i] != nullptr && current->next[i]->value == value){
                return true; // found the value at level i
            }
            // move down a level, if possible 
        }  
        return false; // value not found, we are at level 0 and to the farthest right at level 0 (value always exists at level 0 if in the list)  
    }

    void ShowForward(){
        cout << "Showing forward:\n";
        for (int i = currentHighestLevelIndex; i >= 0;i--){
            Node *node = head->next[i];
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
