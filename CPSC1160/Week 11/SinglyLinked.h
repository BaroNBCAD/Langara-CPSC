#ifndef SINGLYLINKED_H
#define SINGLYLINKED_H

#include <iostream>

using namespace std;

class Node
{
public: // violating OOP rules to speed up learning!
    int data;
    Node *next; // connection/link to the next node

    Node()
    {
        data = 0;
        next = nullptr;
    }

    Node(int d)
    {
        data = d;
        next = nullptr;
    }
};

class LinkedList
{
private:
    Node *head; // pointer to the first node
    Node *tail; // pointer to  the last node

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(int n)
    {
        // adds n nodes to the linked ist where each node contains a 0
        head = tail = nullptr;

        for (int i = 0; i < n; i++)
        {
            AddNodeLast(i);
        }
    }

    ~LinkedList()
    {
        Clear();
    }

    void Clear()
    {
        while (!IsEmpty())
        {
            RemoveFirst();
        }
        head = tail = nullptr;
    }
    
    void AddFirst(int val)
    {
        Node *newNode = new Node(val);
        if (IsEmpty())
        {
            head = tail = newNode;
            return;
        }
        else
        {
            Node *tempAdressHolder = head;
            head = newNode;
            head->next = tempAdressHolder;
        }
    }
    
    int RemoveFirst()
    {
        if (IsEmpty())
        {
            cout << "Linked list already empty, returning 0!" << endl;
            return 0;
        }
        Node *temp = head->next;
        int tempData = head->data;
        //cout << "removed " << tempData << endl;
        delete head;
        head = temp;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        return tempData;
    }
    
    Node* GetLast(){
        return tail;
    }

    Node* Get(int i)
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return nullptr;
        }
        if (i >= Size() || i < 0)
        {
            cout << "Index is Invalid. Returning nullptr." << endl;
            return nullptr;
        }

        Node *temp = head;
        int count = 0;
        while (count < i)
        {
            temp = temp->next;
            count++;
        }
        return temp;
    }

    void AddNodeLast(int value)
    {
        Node *newNode = new Node(value);
        if (IsEmpty())
        {
            head = newNode;
            tail = head;
        }
        else
        {
            tail->next = newNode;
            tail = tail->next;
        }
    }

    int RemoveLast()
    {
        if (IsEmpty())
        {
            cout << "List is empty! returning 0\n";
            return 0;
        }

        if (head == tail)
        {
            int temp = head->data;
            delete head;
            head = tail = nullptr;
            return temp;
        }
        else
        {
            Node *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            temp->next = nullptr;
            int tempData = tail->data;
            delete tail;

            tail = temp;

            return tempData;
        }
    }

    void Add(int index, int val){
        if(index < 0 || index > Size()){
            cout << "invalid index\n";
            return;
        }

        if(IsEmpty()){
            cout << "list is empty\n";
            return;
        }

        if (index == 0){
            AddFirst(val);
            return;
        }
        else if(index == Size()){
            AddNodeLast(val);
            return;
        }

        Node* newNode = new Node(val);

        Node* beforeIndex = Get(index - 1);

        newNode->next = beforeIndex->next;
        beforeIndex->next = newNode;

    }

    int Remove(int i){
        if(IsEmpty()){
            cout << "list is empty\n";
            return 0;
        }

        if(i < 0 || i >= Size()){
            cout << "invalid index. returning 0\n";
            return 0;
        }

        if(i == 0){
            return RemoveFirst();
        }

        if(i == Size() - 1){
            return RemoveLast();
        }

        // i is somewhere in the middle
        Node* toDelete = Get(i);
        Node* before = Get(i - 1);

        before->next = toDelete->next;
        int temp = toDelete->data;

        delete toDelete;
        return temp;


    }
    bool IsEmpty()
    {
        return head == nullptr;
    }



    void Reverse(){
        if(!head || !head->next) return; // empty and single node case
        Node *prev = nullptr;
        Node *temp = head;
        Node *next = head->next;
        tail = head;
        while(next){
            temp->next = prev;
            prev = temp;
            temp = next;
            next = next->next;
        }
        temp->next = prev;
        head = temp;

    }

    void Display()
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return;
        }
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << ", ";
            // move to the next node
            temp = temp->next;
        }

        cout << endl;
    }

    int Size()
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return 0;
        }
        // khoa
        int num = 0;
        Node *temp = head;
        while (temp != nullptr)
        {
            num++;
            temp = temp->next;
        }
        return num;
    }

    Node *Search(int value)
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return nullptr;
        }
        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->data == value)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

#endif