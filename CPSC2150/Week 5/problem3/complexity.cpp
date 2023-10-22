#include <iostream>
#include <string>
#include <ctime>
#include <chrono> //for counting time
#include "SortingQuickMerge.cpp"
#include "HashingSeparateChaining.h"

using namespace std;
using namespace std::chrono;

const int string_length[] = {100, 4000, 16000};
const int trials[] = {50, 150, 300};

string GenerateRandomString(int length){
    string result = "";
    for (int i =0; i < length; i++){
        result += 'a' + rand()%26;
    }
    return result;
}

void DisplayResult(int string_length, int trial, double result){
    cout << "String length: " << string_length << endl;
    cout << "Trials: "  << trial << endl;
    cout << "Result: " << result << endl;
    cout << "--------------------------" << endl;
}

bool testOne_function(string given_string){
    for (int i = 0; i < given_string.length()-1; i++){
        // It should be char to_loof_for = given_string[i]
        // However, I want to test the worst case where this function has to return false.
        char to_look_for = 'A';
        for (int j = i+1; j < given_string.length(); j++){
            if (to_look_for == given_string[j])
                return true;
        }
    }
    return false;

}

void testOne(){
    cout << "Test 1" << endl;
    for (int i =0; i < 3; i++){
        for (int trial_global = 0; trial_global < 3; trial_global++){
            int trial = trials[trial_global];
            auto total_time = 0;
            for (int j = 0; j < trial; j++){
                string given_string = GenerateRandomString(string_length[i]);
                auto beg = high_resolution_clock::now();

                testOne_function(given_string);

                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - beg);
                total_time += duration.count();
            }
            double result_of_time = total_time/(double)trial;
            DisplayResult(string_length[i], trial, result_of_time);
        }
    }
    cout << "Test done" << endl;
}

bool testTwo_function(string given_string){

    /*
    //Using MergeSort
    string sorted_string = MergeSort(given_string);
    for (int i = 0; i < given_string.length()-1; i++){
        // should be char to_look_for = given_string[i];
        // However, I want to test the worst case.
        char to_look_for = 'A';
        if (to_look_for == given_string[i+1])
            return true;
    }
    return false;

    */

    //Using SKipList:
    SkipList sorted_string(2);

    //O(nlogn)
    for (int i = 0; i < given_string.length()-1; i++){
        sorted_string.InsertElement(given_string[i]);
    }

    //O(nlogn)
    for (int i = 0; i < given_string.length()-1; i++){
        // should be char to_look_for = given_string[i];
        // However, I want to test the worst case.
        char to_look_for = 'A';
        if (sorted_string.Search(given_string[i]))
            return true;
    }
    return false;

}

void testTwo(){
    cout << "Test 2" << endl;
    for (int i =0; i < 3; i++){
        for (int trial_global = 0; trial_global < 3; trial_global++){
            int trial = trials[trial_global];
            auto total_time = 0;
            for (int j = 0; j < trial; j++){
                string given_string = GenerateRandomString(string_length[i]);
                auto beg = high_resolution_clock::now();
                
                testTwo_function(given_string);

                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - beg);
                total_time += duration.count();
            }
            double result_of_time = total_time/(double)trial;
            DisplayResult(string_length[i], trial, result_of_time);
        }
    }
    cout << "Test done" << endl;
}

bool testThree_function(string given_string){
    HashingSeparateChaining hashingTable; // just a default table.
    for (int i = 0; i < given_string.length(); i++)
        hashingTable.Insert(given_string[i]);
    
    for (int i =0; i < given_string.length(); i++){
        // should be char to_look_for = given_string[i];
        // I want to test the worst case.
        char to_look_for = 'A';
        if (hashingTable.Search(to_look_for))
            return true;
    }
    return false;
}

void testThree(){
    cout << "Test 3" << endl;
    for (int i =0; i < 3; i++){
        for (int trial_global = 0; trial_global < 3; trial_global++){
            int trial = trials[trial_global];
            auto total_time = 0;
            for (int j = 0; j < trial; j++){
                string given_string = GenerateRandomString(string_length[i]);
                auto beg = high_resolution_clock::now();
                
                testThree_function(given_string);

                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - beg);
                total_time += duration.count();
            }
            double result_of_time = total_time/(double)trial;
            DisplayResult(string_length[i], trial, result_of_time);
        }
    }
    cout << "Test done" << endl;
}


int main(){
    srand(time(0));
    system("CLS");
    int input = -1;
    do{
    cout << "-------------------" << endl;
    cout << "0. Exit" << endl;
    cout << "1. Test 1" << endl;
    cout << "2. Test 2" << endl;
    cout << "3. Test 3" << endl;
    cout << "-------------------" << endl;
    cout << "Get input: "; cin >> input;

    switch(input){
        case 0: return 0;
        case 1: system("CLS"); testOne(); break;
        case 2: system("CLS"); testTwo(); break;
        case 3: system("CLS"); testThree(); break;
        default: system("CLS"); input = -1;
    }

    } while (input != 0);

    return 0;
}
