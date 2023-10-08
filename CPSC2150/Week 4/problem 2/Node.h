/*
    cre: Danny Oct/7
    Source: using code provided by Muntaseer
*/

#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

// the node
class Node{
public:
    int value;
    int priority;
    // Array of pointers to the next nodes (which may be located at various levels)
    // next[i] is the next link for level i
    // the size of this vector determines the number of levels that the current node is part of
    vector<Node*> next; 
    vector<Node*> prev; // previous links for each level the node is part of 

    Node(int val, int level){
        priority = level;
        value = val;
        next = vector<Node*>(level+1, nullptr); // initialize array of pointers to nulls
        prev = vector<Node*>(level+1, nullptr); // initialize array of pointers to nulls
    };
};

#endif
