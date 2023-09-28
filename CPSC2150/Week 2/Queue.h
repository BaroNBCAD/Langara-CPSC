#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include "LinkedListFull.h"

using namespace std;

class Queue
{
private:
    LinkedList<long long int> data;
    int size;

public:
    /**
     * Default constructor. Initializes the size to 0.
     *
     * @param none
     * 
     * @return a Queue object.
     * 
     * @complexity O(1) in the worst case.
     */
    Queue()
    {
        size = 0; // O(1)
    }

    /**
     * Adds an element to the rear of the queue.
     *
     * @param long long int, the element to be added.
     * 
     * @return none
     * 
     * @complexity O(1) in the worst case. See addLast() in LinkedListFull.h.
     */
    void Enqueue(long long int element)
    {
        data.addLast(element); // O(1)
        size++; // O(1)
    }

    /**
     * Removes an element from the front of the queue and returns it. If the queue is empty, outputs a message to the console and returns 0.
     *
     * @param none
     * 
     * @return long long int, the element removed.
     * 
     * @complexity O(1) in the worst case. See removeFirst() in LinkedListFull.h.
     */
    long long int Dequeue()
    {
        if (IsEmpty()) // O(1)
        {
            cout << "Queue is empty" << endl;// O(1)
            return 0;// O(1)
        }

        long long int element = data.getFirst();// O(1)
        data.removeFirst();// O(1)
        size--;// O(1)
        return element;// O(1)
    }

    /**
     * Returns the element at the front of the queue. If the queue is empty, outputs a message to the console and returns 0.
     *
     * @param none
     * 
     * @return long long int, the element at the front of the queue.
     * 
     * @complexity O(1) in the worst case. See getFirst() in LinkedListFull.h.
     */
    long long int PeekFront()
    {
        if (IsEmpty()) // O(1)
        {
            cout << "Queue is empty" << endl; // O(1)
            return 0; // O(1)
        }

        return data.getFirst(); // O(1)
    }

    /**
     * Returns the element at the rear of the queue. If the queue is empty, outputs a message to the console and returns 0.
     *
     * @param none
     * 
     * @return long long int, the element at the rear of the queue.
     * 
     * @complexity O(1) in the worst case. See getLast() in LinkedListFull.h.
     */
    long long int PeekRear()
    {
        if (IsEmpty()) // O(1)
        {
            cout << "Queue is empty" << endl; // O(1)
            return 0; // O(1)
        }

        return data.getLast(); // O(1)
    }

    /**
     * Returns true if the queue is empty, false otherwise.
     *
     * @param none
     * 
     * @return boolean, true if the queue is empty, false otherwise.
     * 
     * @complexity O(1) in the worst case.
     */
    bool IsEmpty()
    {
        return size == 0; // O(1)
    }

    /**
     * displays the elements of the queue.
     *
     * @param none
     * 
     * @return none
     * 
     * @complexity O(n) in the worst case where n is the number of elements in the queue. See Show() in LinkedListFull.h.
     */
    void Show()
    {
        data.Show(); // O(n)
    }    

};


#endif