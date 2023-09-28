#ifndef NODE_H
#define NODE_H


template<typename T>
class Node
{
public:
  T element;  // Element contained in the node
  Node<T> *next; // Pointer to the next node

  Node() // No-arg constructor
  {
    next = NULL;
  }

  Node(T element) // Constructor
  {
    this->element = element;
    next = NULL;
  }
};


#endif