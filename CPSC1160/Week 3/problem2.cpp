#include <iostream>

using namespace std;

void IncreaseSize(int* &arr, int *oldSize, int *newSize, int *i){
    if(*oldSize == *newSize){
        return;
    }
    else if(*oldSize > *newSize){
        delete[] arr;
        arr = nullptr;
        *newSize = 0;
        return;
    }
    else{
        int* newArr = new int[*newSize];
        for (*i = 0; *i < *oldSize; (*i)++){
            newArr[*i] = arr[*i];
        }
        for(*i = *oldSize; *i < *newSize; (*i)++){
            newArr[*i] = 0;
        }
        delete[] arr;
        arr = newArr;
        return;
    }
}

void DecreaseSize(int* &arr, int *oldSize, int *newSize, int *i){
    if(*oldSize == *newSize){
        return;
    }
    else if(*oldSize < *newSize){
        delete[] arr;
        arr = nullptr;
        *newSize = 0;
        return;
    }
    else{
        int* newArr = new int[*newSize];
        for (*i = 0; *i < *newSize; (*i)++){
            newArr[*i] = arr[*i];
        }
        delete[] arr;
        arr = newArr;
        return;
    }
}

void Display(int* arr, int *size, int *i){
    for(*i = 0; *i < *size; (*i)++){
        cout << arr[*i] << ", ";
    }
    cout << endl;
}

int main(){
    int *i = new int(0);

    int *arrSize = new int(3);
    int *arr = new int[*arrSize];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    int* newSize = new int(5);

    IncreaseSize(arr, arrSize, newSize, i);

    Display(arr, newSize, i);

    *arrSize = 2;

    DecreaseSize(arr, newSize, arrSize, i);

    Display(arr, arrSize, i);

    if(arr != nullptr){
        delete[] arr;
        arr = nullptr;
    }

    if(arrSize != nullptr){
        delete arrSize;
        arrSize = nullptr;
    }

    if(newSize != nullptr){
        delete newSize;
        newSize = nullptr;
    }

    if(i != nullptr){
        delete i;
        i = nullptr;
    }
    
    return 0;
}