#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

using namespace std;

class DynamicArray{
private:
    int* array;
    int size;

public:
    DynamicArray(){
        array = nullptr;
        size = 0;
    }

    DynamicArray(int n){
        size = n;
        array = new int[size];
        for(int i = 0; i < size; i++){
            array[i] = 0;
        }
    }

    DynamicArray(int *arr, int n){
        size = n;
        // array = arr; // shallow copying - dangerous!
        // deep copy - better!
        array = new int[size];
        for(int i = 0; i < size; i++){
            array[i] = arr[i];
        }
    }

    // copy constructor
    DynamicArray(const DynamicArray &source){
        size = source.size;
        array = new int[size];
        for(int i = 0; i < size; i++){
            array[i] = source.array[i];
        }
    }
    
    void Clear(){
        if(array != nullptr){
            delete[] array;
            array = nullptr;
        }
        size = 0;
    }
    // destructor
    ~DynamicArray(){
        Clear();
    }

    bool IsEmpty(){
        return size == 0;
    }

    void Display(){
        if(IsEmpty()){
            cout << "array is empty!\n";
            return;
        }

        for(int i = 0; i < size - 1 ; i++){
            cout << array[i] << ", ";            
        }
        cout << array[size - 1] << ".\n";
    }

    int GetSize(){
        return size;
    }

    ////////////////////////////////////
    //index == 0: add from the first node
    //index == size: add to the last
    //index == i: add from ith
    void Add(int index, int* newItems, int newItemsSize){
        if (index < 0 || index > size){
            cout << "invalid index" << endl;
            return;
        }
        if (newItems == nullptr || newItemsSize ==0){
            cout << "invalid newItems/newItemsSize" << endl; 
            return;
        }
        //newArray: to store the result array
        int* newArray = new int[size+newItemsSize];
        int i = 0; //to keep track with newArray index
        for (;i<index;i++){
            newArray[i] = array[i];
        }
        for (int j = 0; j < newItemsSize; j++){
            newArray[i++] = newItems[j]; 
        }
        for (;i<size+newItemsSize;i++){
            newArray[i] = array[i-newItemsSize];
        }

        delete[] array;
        array = newArray;
        size += newItemsSize;
        return;
    }

    ////////////////////////////////////
    void Remove(int index1, int index2){
        if ((index1>=0) && (index1 <= index2) && (index2<size)){
            //index2-index1+1 is the number of removed nodes.
            int newSize = size - (index2 - index1 + 1);
            if (newSize == 0){
                delete[] array;
                array = nullptr;
                size = newSize;
                return;
            }
            int* newArray = new int[newSize];
            for (int i =0; i < index1; i++){
                newArray[i] = array[i];
            }
            for (int i =index2+1; i < size; i++){
                newArray[i-(index2-index1+1)] = array[i];
            }

            delete[] array;
            array = newArray;
            size = newSize;
            return;
        }
        else{
            cout << "invalid indices." << endl;
            return;
        }
    }
    ////////////////////////////////////
    void MergeInOrder(int* left, int lSize, int* right, int rSize) {
	
        int i, j, k;
        int* merged = new int[lSize + rSize];
        i = j = k = 0;

        while (i < lSize && j < rSize) {
            if (left[i] <= right[j]) {
                merged[k++] = left[i++];
            }
            else {
                merged[k++] = right[j++];
            }
        }

        while (i < lSize) {
            merged[k++] = left[i++];
        }
        while (j < rSize) {
            merged[k++] = right[j++];
        }

        for (int m =0; m < lSize+rSize; m++){
            left[m] = merged[m];
        }
        delete[] merged;
    }

    void MergeSort(int* p, int n){
        if (n < 2)
            return;
        int middlePoint = n/2;
        MergeSort(p, middlePoint);
        MergeSort(p+middlePoint, n-middlePoint);
        MergeInOrder(p, middlePoint, p+middlePoint, n-middlePoint);
        return;
    }

    void Sort(int index1, int index2){
        if ((index1>=0) && (index1 <= index2) && (index2<size)){
            int sortingSize = index2 - index1 + 1;
            MergeSort(array+index1, sortingSize);
            return;
        }
        else{
            cout << "invalid indices." << endl;
            return;
        }
    }

    ////////////////////////////////////////
    DynamicArray& operator=(const DynamicArray& rhs){
        if (this != &rhs){
            delete[] array;
            size = rhs.size;
            array = new int[size];
            for(int i = 0; i < size; i++){
                array[i] = rhs.array[i];
            }
        }
        return *this;
    }
    ////////////////////////////////////////
    bool operator==(const DynamicArray& rhs) const{
        if (size == rhs.size){
            for(int i = 0; i < size; i++){
                if (array[i] != rhs.array[i]) return false;
            }
            return true;
        }
        return false;
    }
    ////////////////////////////////////////
    DynamicArray& operator+(const DynamicArray& rhs){
        DynamicArray* result = new DynamicArray(this->size+rhs.size);
        int j = 0;
        for (; j < size; j++){
            result->array[j] = this->array[j];
        }
        for (; j < size+rhs.size; j++){
            result->array[j] = rhs.array[j-size];
        }
        return *result;
    }
    ////////////////////////////////////////
    void operator+=(const DynamicArray& rhs){
        if (rhs.size != 0){
            this->Add(size, rhs.array, rhs.size);
        }
    }
};
#endif