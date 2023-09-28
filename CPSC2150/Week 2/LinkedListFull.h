#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <stdexcept>
#include "Node.h"
using namespace std;

template<typename T>
class LinkedList
{
public:
  
LinkedList()
{
  head = tail = NULL;
  size = 0;
}


    /**
     * Removes the last element from the linked list. Recursively arrives at the last node while keeping track of the previous node; then deletes the last node and returns the element removed.
     *
     * @param none
     * 
     * @return The removed element (an instance of T).
     * 
     * @complexity O(n) in the worst case, where n is the number of elements in the list as node previous to tail must be found.
     */
    T removeLast()
    {
        if (size == 0)
        {
            cout << "No elements in the list" << endl;
            return T();
        }

        if (size == 1)
        {
            T element = head->element;
            delete head;
            head = tail = nullptr;
            size = 0;
            return element;
        }

        return removeLastRecursive(head, nullptr);
    }

    T removeLastRecursive(Node<T> *current, Node<T> *previous)
    {
        if (current->next == nullptr)
        {
            T element = current->element;
            delete current;
            previous->next = nullptr;
            size--;
            return element;
        }
        return removeLastRecursive(current->next, current);
    }

    /**
     * Adds an element at the specified index in the linked list. Recursively arrives at the node before the index at which to add the element; then adds the element and returns.
     *
     * @param index integer, The index at which to add the element.
     * @param element The element to be added (an instance of T).
      *
      * @return none
      * 
     * @complexity O(1) worst case if adding as first or last; O(n) worst case else where, where n is the number of elements in the list as node previous to index must be found.
     */
    void add(int index, T element)
    {
        if (index < 0 || index > size)
        {
            cout << "Invalid index" << endl;
            throw out_of_range("Invalid index");
        }

        if (index == 0)
        {
            addFirst(element);
        }
        else if (index == size)
        {
            addLast(element);
        }
        else
        {
            addRecursive(head, index, element, 0);
        }
    }

    void addRecursive(Node<T> *current, int index, T element, int currentIndex)
    {
        if (currentIndex + 1 == index)
        {
            Node<T> *newNode = new Node<T>(element);
            newNode->next = current->next;
            current->next = newNode;
            size++;
        }
        else
        {
            addRecursive(current->next, index, element, currentIndex + 1);
        }
    }

    /**
     * Clears the linked list by removing all elements. Recursively arrives at the last node and deletes it; then sets head and tail to nullptr and size to 0.
     * 
     * @param none
     * 
     * @return none
     *
     * @complexity O(n), where n is the number of elements in the list as all nodes must be deleted.
     */
    void clear()
    {
        clearRecursive(head);
        head = tail = nullptr;
        size = 0;
    }

    void clearRecursive(Node<T> *current)
    {
        if (current != nullptr)
        {
            clearRecursive(current->next);
            delete current;
        }
    }

    /**
     * Checks if the linked list contains a specific element. Recursively traverses the list until the element is found or the end of the list is reached.
     *
     * @param element The element to check for (an instance of T).
     * 
     * @return bool, true if the element is found, false otherwise.
     * 
     * @complexity O(n) in the worst case, where n is the number of elements in the list as all nodes must be checked.
     */
    bool contains(T element)
    {
        return containsRecursive(head, element);
    }

    bool containsRecursive(Node<T> *current, T element)
    {
        if (current == nullptr)
        {
            return false;
        }
        if (current->element == element)
        {
            return true;
        }
        return containsRecursive(current->next, element);
    }

    /**
     * Displays the elements of the linked list.
     * 
     * @param none
     * 
     * @return none
     *
     * @complexity O(n), where n is the number of elements in the list as all nodes must be displayed.
     */
    void Show()
    {
        ShowRecursive(head);
        cout << endl;
    }

    void ShowRecursive(Node<T> *current)
    {
        if (current != nullptr)
        {
            cout << current->element << " -> ";
            ShowRecursive(current->next);
        }
    }

void addFirst(T element)
{
  Node<T> *newNode = new Node<T>(element);
  newNode->next = head;
  head = newNode;
  size++;

  if (tail == NULL)
    tail = head;
}


void addLast(T element)
{
  if (tail == NULL) // O(1)
  {
    head = tail = new Node<T>(element); // O(1)
  }
  else {
    tail->next = new Node<T>(element); // O(1)
    tail = tail->next; // O(1)
  }

  size++; // O(1)
}


T getFirst() const
{
  if (size == 0) // O(1)
    throw runtime_error("Index out of range");
  else
    return head->element; // O(1)
}


T getLast() const
{
  if (size == 0) // O(1)
    throw runtime_error("Index out of range");
  else
    return tail->element; // O(1)
}


T removeFirst() throw (runtime_error)
{
  if (size == 0)// O(1)
   throw runtime_error("No elements in the list");
  else
  {
    Node<T> *temp = head;// O(1)
    head = head->next;// O(1)
    size--;// O(1)
    T element = temp->element;// O(1)
    delete temp;// O(1)
    return element;// O(1)
  }
}



void add(T element)
{
  addLast(element);
}


T get(int index) const
{
  if (index < 0 || index > size - 1)
    throw runtime_error("Index out of range");

  Node<T> *current = head;
  for (int i = 0; i < index; i++)
    current = current->next;

  return current->element;
}


int indexOf(T element) const
{
  // Implement it in this exercise
  Node<T> *current = head;
  for (int i = 0; i < size; i++)
  {
    if (current->element == element)
      return i;
    current = current->next;
  }

  return -1;
}


bool isEmpty() const
{
  return head == NULL;
}


int getSize() const
{
  return size;
}


T remove(int index)
{
  if (index < 0 || index >= size){
    cout << "Index out of range" << endl;
    return 0;
  }
  else if (index == 0)
    return removeFirst();
  else if (index == size - 1)
    return removeLast();
  else {
    Node<T> *previous = head;

    for (int i = 1; i < index; i++)
    {
      previous = previous->next;
    }

    Node<T> *current = previous->next;
    previous->next = current->next;
    size--;
    T element = current->element;
    delete current;
    return element;
  }
}

bool remove(T element)
{
  Node<T> *previous = head;
  Node<T> *current;

  if (head != NULL)
  {
    if (element == head->element)
    {
      head = head->next;
      size--;
      return true;
    }
    else
    {
      current = head->next;
    }
  }
  else
    return false;

  for (int i = 0; i < size - 1; i++)
  {
    if (element == current->element) {
      previous->next = current->next; // Remove the current element
      size--;
      return true;
    }
    else
    {
      previous = current;
      current = current->next;
    }
  }

  return false;
}


int lastIndexOf(T element) const
{
  int lastIndex = -1;
  Node<T> *current = head;
  for (int i = 0; i < size; i++)
  {
    if (current->element == element)
      lastIndex = i;
    current = current->next;
  }

  return lastIndex;
}


T set(int index, T element)
{
  if (index < 0 || index >= size)
    throw runtime_error("Index out of range");

  Node<T> *current = head;
  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }

  T oldElement = current->element;
  current->element = element;
  return oldElement;
}

private:
  Node<T> *head, *tail;
  int size;
};

#endif
