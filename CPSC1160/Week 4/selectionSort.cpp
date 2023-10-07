/*

    Recursive SelectionSort: using professor Muntaseer's method

*/
#include <iostream>
#include <ctime>

using namespace std;

void ForLoop2(double list[], int listSize, int j, double* currentMin, int* currentMinIndex){
    if (j < listSize){
        if (*currentMin >list[j]){
            *currentMin = list[j];
            *currentMinIndex=j;
        }
        ForLoop2(list, listSize, j+1, currentMin, currentMinIndex);
    }

}

void ForLoop1(double list[], int listSize, int i){
    if (i < listSize){
        double* currentMin = new double;
        *currentMin = list[i];
        int* currentMinIndex = new int;
        *currentMinIndex = i;

        ForLoop2(list, listSize, i+1, currentMin, currentMinIndex);
        if (*currentMinIndex != i){
            list[*currentMinIndex] = list[i];
            list[i] = *currentMin;
        }
        delete currentMin;
        currentMin = nullptr;
        delete currentMinIndex;
        currentMinIndex = nullptr;
        ForLoop1(list, listSize, i+1);
    }
}

void selectionSort(double list[], int listSize){
    if (listSize == 0 || listSize == 1)
        return;    
    ForLoop1(list, listSize, 0);
}

int main(){
    srand(time(0));
    double* list = new double[10];

    for (int i =0; i < 10; i++){
        list[i] = (rand()%901+100)/100.00;
        cout << list[i] << " ";
    }
    cout << endl;
    selectionSort(list, 10);
    for (int i =0; i < 10; i++){
        cout << list[i] << " ";
    }
    cout << endl;
    delete[] list;
    list=nullptr;
    return 0;
}
