/*
  Danny
*/
#include <iostream>
#include "liangAVLTree.h"
#include <ctime>
using namespace std;

int main(){
    srand(time(0));
    cout << "LevelOrderDisplay()/remove() tests: " <<endl;
    AVLTree test;
    test.insert(25);
    test.insert(20);
    test.insert(5);
    test.LevelOrderDisplay();
    cout << "---" << endl;
    test.insert(34);
    test.insert(50);
    test.LevelOrderDisplay();
    cout << "---" << endl;
    test.insert(30);
    test.LevelOrderDisplay();
    cout << "---" << endl;
    test.insert(10);
    test.LevelOrderDisplay();
    cout << "---" << endl;
    test.remove(34);
    test.remove(30);
    test.remove(50);
    test.LevelOrderDisplay();
    cout << "---" << endl;
    test.remove(5);
    test.LevelOrderDisplay();
    cout << "---" << endl;
    //////////////////////////////////////////////
    cout << "Imbalance handling tests: " <<endl;
    for (int i = 0; i < 20; i++){
        test.insert(rand()%100);
    }
    test.DisplayTreeHorizontally();
    //////////////////////////////////////////////
    cout << "CountNodesAtLevel() tests: " <<endl;
    for (int i = -1; i <= 6; i++){
        cout << "Nodes at level " << i << ": " <<test.CountNodesAtLevel(i) << endl;
    }
    //////////////////////////////////////////////
    cout << "Count() min max tests: " <<endl;
    int min = 10;
    int max = 50;
    cout << "Number of nodes between " << min << " and " << max << ": " <<test.Count(min, max) << endl;
    //////////////////////////////////////////////
    cout << "Diameter(): " <<endl;
    test.DisplayTreeHorizontally();
    cout << "Diameter: "<< test.Diameter() << endl;
    return 0;
}