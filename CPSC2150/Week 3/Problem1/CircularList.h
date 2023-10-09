#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    int id;
    int data;
    Node* next;

    Node(int _id, int value) : id(_id), data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* last;

public:
    CircularLinkedList() : last(nullptr) {}
    ~CircularLinkedList(){
        if (last == nullptr)    return;
        Node* head = last->next;
        last->next = nullptr;
        while (head != nullptr){
            Node* temp = head->next;
            delete head;
            head=temp;
        }
    }
    // Check if the circular linked list is empty
    bool isEmpty() {
        return last == nullptr;
    }

    // Get the last node in the circular linked list
    Node* getLast() {
        return last;
    }

    // Insert a new node with data at the end of the circular linked list
    void insert(int id, int data) {
        Node* new_node = new Node(id, data);
        if (!last) {
            last = new_node;
            last->next = last;
        } else {
            new_node->next = last->next;
            last->next = new_node;
            last = new_node;
        }
    }

    // Delete a node with the given data
    void deleteNode(int data) {
        if (!last)
            return;

        Node* current = last->next;
        Node* previous = nullptr;

        while (current->next != last->next) {
            if (current->data == data) {
                if (current == last->next)
                    last->next = last->next->next;
                if (current == last)
                    last = previous;
                if (previous)
                    previous->next = current->next;
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }

        if (current->data == data) {
            if (current == last->next)
                last->next = last->next->next;
            if (current == last)
                last = previous;
            if (previous)
                previous->next = current->next;
            delete current;
        }
    }

    // Search for a node with the given data
    bool search(int data) {
        if (!last)
            return false;

        Node* current = last->next;

        do {
            if (current->data == data)
                return true;
            current = current->next;
        } while (current != last->next);

        return false;
    }

    // display all elements in the circular linked list
    void display() {
        if (!last)
            return;

        Node* current = last->next;

        do {
            cout << "ID: " << current->id << ", Process Time: " << current->data << endl;
            current = current->next;
        } while (current != last->next);

        cout << endl;
    }
};

#endif
