#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

void displayArr(int** arr, int r, int c, int rowIndex, int colIndex){
    if (rowIndex == r-1 && colIndex == c){
        cout << endl <<"-   -   -" << endl;
        return;
    }
    if (colIndex==c){
        colIndex=0;
        rowIndex++;
        cout << endl <<"-   -   -" << endl;
    }
    cout << setw(2) << arr[rowIndex][colIndex] << " |";
    displayArr(arr, r, c, rowIndex, colIndex+1);
}

void displayArr(int** arr, int r, int c){
    displayArr(arr, r, c, 0, 0);
}

void assignValues(int** arr, int r, int c, int rowIndex, int colIndex){
    if (rowIndex == r-1 && colIndex == c){
        return;
    }
    if (colIndex==c){
        colIndex=0;
        rowIndex++;
        arr[rowIndex] = new int[c];
    }
    arr[rowIndex][colIndex]=rand()%99+1;
    assignValues(arr, r, c, rowIndex, colIndex+1);
}

int** assignValues(int** arr, int r, int c){
    arr = new int*[r];
    arr[0] = new int[c];
    assignValues(arr, r, c, 0, 0);
    return arr;
}

void deallocate(int** arr, int r, int rowIndex){
    if (rowIndex == r){
        return;
    }
    delete[] arr[rowIndex];
    assignValues(arr, r, rowIndex+1);
}

int** deallocate(int** arr, int r){
    deallocate(arr,r,0);
    delete[] arr;
    return nullptr;
}

int HasEvenSum(int** arr, int r, int c, int rowIndex, int colIndex){
    if (rowIndex == r-1 && colIndex == c){
        return 0;
    }
    if (colIndex==c){
        colIndex=0;
        rowIndex++;
    }

    return (arr[rowIndex][colIndex]%2) + HasEvenSum(arr, r, c, rowIndex, colIndex+1);

}


bool HasEvenSum(int** arr, int r, int c){
    if (r<0 || c<0){
        cout << "Failed. ie Rows || Cols is invalid" << endl;
        return false;
    }
    if (arr == nullptr){
        cout << "Failed. ie arr == nullptr" << endl;
        return false;
    }
    
    return !(HasEvenSum(arr, r, c, 0, 0)%2);
}

int main(){
    srand(time(0));
    const int rows = 2;
    const int cols = 5;
    int** array;
    array = assignValues(array, rows, cols);
    displayArr(array, rows, cols);
    cout << HasEvenSum(array, rows, cols) << endl;
    array = deallocate(array,rows);

    return 0;
}
