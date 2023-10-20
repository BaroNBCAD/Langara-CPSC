#include <iostream>
#include <ctime>
#include "HashingLinearProbingDemo.h"

using namespace std;

void insert_function(HashingLinearProbingDemo &test){
    int value = rand()%1000 + 1;
    test.Insert(value);
    cout << "Insert() function done" << endl;
    return;
}

void delete_function(HashingLinearProbingDemo &test){
    int numDel = 0;
    cout <<"Delete number?: "; cin >> numDel;
    system("CLS");
    if(test.Delete(numDel))
        cout << numDel << " is deleted" << endl;
    else
        cout << "Fail to delete number " << numDel << endl;
    return;
}

void search_function(HashingLinearProbingDemo &test){
    int numSea = 0;
    cout <<"Search number?: "; cin >> numSea;
    system("CLS");
    if(test.Search(numSea))
        cout << numSea << " is found" << endl;
    else
        cout << numSea << " is not found" << endl;
    return;
}

void display_function(HashingLinearProbingDemo &test){
    test.Display();
    return;
}

int main(){
    system("CLS");
    srand(time(0));
    HashingLinearProbingDemo test;
    int input = -1;
    do{
        display_function(test);
        cout << "-------------" << endl;
        cout << "0. Exit" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "-------------" << endl;
        cout << "Get input: "; cin >> input;
        
        switch(input){
            case 0: return 0;
            case 1: system("CLS"); insert_function(test); break;
            case 2: delete_function(test); break;
            case 3: search_function(test); break;
            default: system("CLS"); input = -1; break;
        }
    }while (input != 0);
    return 0;
}