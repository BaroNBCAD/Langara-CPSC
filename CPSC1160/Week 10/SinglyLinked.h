/*
    Danny (with help from other students' code for some functions)
*/

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
    // farhan
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
    // jimmy
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

    // harold
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

    void RemoveLast()
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return;
        }

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            temp->next = nullptr;
            delete tail;

            tail = temp;
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
    //Idk what this function is.
    int Remove(int i){

    }

    bool IsEmpty()
    {
        return head == nullptr;
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

    // hassan
    Node *Max()
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return nullptr;
        }
        Node *max = head;
        for (Node *temp = head->next; temp != nullptr; temp = temp->next)
        {
            if (max->data < temp->data)
                max = temp;
        }
        return max;
    }

    // harold
    int Sum()
    {
        if (IsEmpty())
        {
            cout << "List is empty!\n";
            return 0;
        }
        Node *temp = head;
        int sum = 0;
        while (temp != nullptr)
        {
            sum = sum + temp->data;
            temp = temp->next;
        }
        return sum;
    }

    //////////////////////////////
    LinkedList(LinkedList& rhs)
    {
        head = tail = nullptr;
        Node* tempRhsHead = rhs.head;
        while (tempRhsHead){
            this->AddNodeLast(tempRhsHead->data);
            tempRhsHead = tempRhsHead->next;
        }
    }

    void Swap(int i, int j){
        //I skip the validating step since out Get() function has validated them.
        Node* tempI = this->Get(i);
        Node* tempJ = this->Get(j);

        /*
            1) same index -> no swap
            2) i is nullptr -> no swap
            3) j is nullptr -> no swap
            You can add specific error message for each case.
        */
        if (i==j || !i || !j)
            return;
        
        int tempData = tempI->data;
        tempI->data = tempJ->data;
        tempJ->data = tempData;
        return;
    }

    bool isRepeated(unsigned int* splitIndices, int index, int value){
        //check the previous value to the current value.
        if (index == 0) return false;
        return splitIndices[index-1] >= value;
    }

    LinkedList* Split(unsigned int* splitIndices, int n){
        // The splitIndices is an ascending array.
        if (!splitIndices || n < 0){ 
            cout << "Invalid inputs." << endl;
            return nullptr;
        }

        if (IsEmpty()){
            cout << "The list is empty." << endl;
            return nullptr;
        }
        int listSize = Size();
        for (int i =0; i < n; i++){
            //splitIndices[i] < 0 is unecessary since it's an unsigned array.
            if (splitIndices[i] < 0 || splitIndices[i] > listSize-1 || isRepeated(splitIndices, i, splitIndices[i])){
                cout << "each value must be between 0 and (number of nodes in linked list – 1) and none of them be repeated" << endl;
                return nullptr;
            }
        }

        LinkedList* result = new LinkedList[n+1];

        Node* temp = head;
        Node* tempHead = head;
        int index = 0;
        int count = 0;
        while (temp != nullptr && index < n){
            if (count == splitIndices[index]){
                result[index].head = tempHead;
                result[index].tail = temp;
                Node* tempNext = temp->next;
                result[index].tail->next = nullptr;
                temp = tempNext;
                tempHead = temp;
                index++;
            }
            else{
                temp=temp->next;
            }
            count++;
        }

        if (temp != nullptr){
            result[index].head = tempHead;
        }
        //Since the new LinkedList objects are taking the original list, our list now is empty
        this->head=nullptr;
        this->tail=nullptr;
        return result;
    }

    /*
        SORTING
        Here I'm sorting the CONTENT of the linked list, instead of sorting the Nodes.
    */
    int* LinkedListToArray(){
        int* result = nullptr;
        int listSize = Size();
        if (listSize == 0) return result;
        result = new int[listSize];
        Node* temp = head;
        int index = 0;
        while (temp){
            result[index++] = temp->data;
            temp=temp->next;
        }
        return result;
    }

    void insertionSort(int* arr, int n)
    {
        for (int i = 1; i < n; i++) {
            int start = arr[i];
            int j = i-1;
            for (; j >= 0 && arr[j] > start; j--){
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = start;
        }
    }

    void InsertionSortList(){
        if (IsEmpty())
            return;
        int listSize = Size();
        int* listToArray = LinkedListToArray();
        insertionSort(listToArray, listSize);
        Node* temp = head;
        int index = 0;
        while (temp){
            temp->data = listToArray[index++];
            temp=temp->next;
        }
        if (listToArray)
            delete[] listToArray;
        return;
    }

    /*
        void MergeSortList(){
            same logic
        }

        void QuickSortList(){
            same logic
        }
    */

    // Assignment operator
    LinkedList& operator=(LinkedList& rhs){
        if (this != &rhs){
            Clear();
            Node* tempRhsHead = rhs.head;
            while (tempRhsHead){
                this->AddNodeLast(tempRhsHead->data);
                tempRhsHead = tempRhsHead->next;
            }
        }
        return *this;
    }

    // +operator
    LinkedList* operator+(LinkedList& rhs){
        LinkedList* result = new LinkedList();
        Node* tempThis = this->head;
        while (tempThis){
            result->AddNodeLast(tempThis->data);
            tempThis = tempThis->next;
        }

        Node* tempRhs = rhs.head;
        while (tempRhs){
            result->AddNodeLast(tempRhs->data);
            tempRhs = tempRhs->next;
        }
        return result;
    }

    // operator+=
    void operator+=(LinkedList& rhs){
        Node* tempRhs = rhs.head;
        while (tempRhs){
            AddNodeLast(tempRhs->data);
            tempRhs=tempRhs->next;
        }
        return;
    }

    //operator-

    LinkedList* operator-(LinkedList& rhs){
        LinkedList* result = new LinkedList();
        if (IsEmpty()) return result;

        Node* tempThis = this->head;
        while (tempThis){
            if (!rhs.Search(tempThis->data))
                result->AddNodeLast(tempThis->data);
            tempThis=tempThis->next;
        }
        return result;
    }

    //opreator<<

    friend ostream& operator<<(ostream& out, LinkedList& object){
        out << "Displaying the list: ";
        if (object.IsEmpty())
        {
            out << "List is empty!\n";
            return out;
        }
        Node *temp = object.head;
        while (temp != nullptr)
        {
            out << temp->data << ", ";
            // move to the next node
            temp = temp->next;
        }
        out << endl;
        return out;
    }

    //operator>>
    friend istream& operator>>(istream& in, LinkedList& object){
        int size = 0;
        cout << "Number of nodes: "; in >> size;
        if (size < 0){
            cout << "Size can not be negative." << endl;
            return in;
        }
        if(!object.IsEmpty())
            object.Clear();

        for (int i=0; i < size; i++){
            int val = INT_MIN;
            cout << "Enter value: "; in >> val;
            object.AddNodeLast(val);
        }

        return in;
    }
};

#endif