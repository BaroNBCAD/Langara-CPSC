/*

    Recursive bubbleSort: using professor Muntaseer's method

*/

#include <iostream>
#include <ctime>

using namespace std;

void Forloop2(int list[], int arraySize, bool* needNextPass, int k, int i){
    if (i < arraySize-k){
        if (list[i] > list[i + 1])
        {
            // Swap list[i] with list[i + 1]
            int temp = list[i];
            list[i] = list[i + 1];
            list[i + 1] = temp;

            *needNextPass = true; 
        }
        Forloop2(list, arraySize, needNextPass, k, ++i);
    }
}

void Forloop1(int list[], int arraySize, bool* needNextPass, int k){
    if (k < arraySize && needNextPass)
    {
        *needNextPass = false;
        Forloop2(list, arraySize, needNextPass, k, 0);
        Forloop1(list, arraySize, needNextPass, k+1);
    }
}

void bubbleSort(int list[], int arraySize)
{
    bool* needNextPass = new bool;
    *needNextPass = true;
    int k = 1;
    Forloop1(list, arraySize, needNextPass, k);
    delete needNextPass;
    needNextPass=nullptr;
}


int main(){
    srand(time(0));
    int* list = new int[10];

    for (int i =0; i < 10; i++){
        list[i] = rand()%15+1;
        cout << list[i] << " ";
    }
    cout << endl;
    bubbleSort(list, 10);
    for (int i =0; i < 10; i++){
        cout << list[i] << " ";
    }
    cout << endl;
    delete[] list;
    list=nullptr;
    return 0;

    return 0;
}
