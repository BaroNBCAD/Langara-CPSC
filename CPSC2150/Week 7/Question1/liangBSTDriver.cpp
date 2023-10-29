#include <iostream>
#include "liangBST.h"
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    const int maxNumOfNodes = 8;
    const int minNumOfNodes = 5;
    const int maxValue = 50;
    const int minValue = 10;
    const int numberOfNodes = rand()%(maxNumOfNodes-minNumOfNodes + 1) + minNumOfNodes;
    int* arrayOfNodes = new int[numberOfNodes];
    for (int i =0; i < numberOfNodes; i++){
        int randomValue = rand()%(maxValue - minValue + 1) + minValue;
        arrayOfNodes[i] = randomValue;
    }
    BST a(arrayOfNodes, numberOfNodes);

    cout << "Display BST a: " << endl;
    a.DisplayTreeHorizontally();
    a.LevelOrderDisplay();
    cout << "----" << endl;

    //COPY Constructor/copy FUNCTION TEST
    cout << "COPY Constructor/copy FUNCTION TEST:" << endl;
    BST b(a);
    cout << "Display b: " << endl;
    b.LevelOrderDisplay();
    cout << "a address: " << &a << endl;
    cout << "b address: " << &b << endl;
    cout << "a firstNode address: " << a.kthSmallest(1) << endl;
    cout << "b firstNode address: " << b.kthSmallest(1)  << endl;

    //SEARCH FUNCTION TEST
    cout << "SEARCH FUNCTION TEST:" << endl;
    int searchNumberTest = 24; // please manually set this number
    TreeNode* testSearch = a.search(searchNumberTest);
    if (testSearch != nullptr)
        cout << testSearch->element << " is found." << endl;
    else
        cout << "It's nullptr." << endl;
    cout << "----" << endl;

    //INORDER FUNCTION TEST
    cout << "INORDER" << endl;
    a.inorder();
    cout << endl << "----" << endl;

    //PREORDER FUNCTION TEST
    cout << "PREORDER" << endl;
    a.preorder();
    cout << endl << "----" << endl;

    //POSTORDER FUNCTION TEST
    cout << "POSTORDER" << endl;
    a.postorder();
    cout << endl << "----" << endl;
    
    //CLEAR FUNCTION TEST
    // I Don't wanna delete the BST yet @@
    // a.clear();
    // if (a.isEmpty())
    //     cout << "It's empty." << endl;
    // else
    //     cout << "It's not empty" << endl;

    //PATH FUNCTION TEST
    cout << "PATH FUNCTION TEST" << endl;
    int searchNumber = 31;  //please manually give value for this
    vector<TreeNode*>* path = a.path(searchNumber); 

    for (int i = 0; i < (*path).size(); i++){
        if ((*path)[i] != nullptr)
            if ((*path)[i]->element != searchNumber)
                cout << (*path)[i]->element << " -> ";
            else
                cout << (*path)[i]->element << endl;
        else
            cout << "nullptr" << endl;
    }
    cout << "----" << endl;

    //GetHeight FUNCTION TEST
    cout << "GetHeight Test: " << a.GetHeight() << endl;
    cout << "----" << endl;

    //IncrementByOne FUNCTION TEST
    cout << "IncrementByOne FUNCTION TEST: " << endl;
    cout << "before: "<< endl;
    a.inorder();
    cout << endl;
    a.IncrementByOne();
    cout << "after: " << endl;
    a.inorder();
    cout << endl;
    cout << "----" << endl;

    //NodeCount FUNCTION TEST
    cout << "NodeCount FUNCTION TEST: " << endl;
    cout << a.NodeCount() << endl;
    cout << "----" << endl;

    //NodesWithOddValues FUNCTION TEST
    cout << "NodesWithOddValues FUNCTION TEST: " << endl;
    a.LevelOrderDisplay();
    cout << a.NodesWithOddValues() << endl;
    cout << "----" << endl;

    //kthSmallest test
    cout << "kthSmallest FUNCTION TEST: " << endl;
    a.inorder();
    cout << endl;
    int testNum = 3; //please set this number manually
    if (a.kthSmallest(testNum) != nullptr){
        cout << a.kthSmallest(testNum)->element << endl;
    }
    else
        cout << "Out of range." << endl;
    
    //ClosestCommonAncestor
    cout << "ClosestCommonAncestor FUNCTION TEST: " << endl;
    a.DisplayTreeHorizontally();
    cout << endl;
    cout << "--" << endl;
    TreeNode* node1 = nullptr;
    TreeNode* node2 = nullptr;
    cout << "Not sure how to test it with random nodes " << endl;
    cout << "However, you may want to do\nnode1 = a.getRoot()->left->right->right->etc\nnode2 = a.getRoot()->left->->right->left->etc" << endl;
    cout << "----" << endl;
    //operator== and operator= tests:
    cout << "If BST a == BST b (false since a went through an incrementByOne: " << (a==b) << endl; //false, since a has gone through incrementOne
    b.IncrementByOne();
    cout << "If BST a == BST b after b went through incrementByOne: " << (a==b) << endl;
    cout << "Address Test: " << a.kthSmallest(1) << " | " << b.kthSmallest(1)  << endl;
    cout << "----" << endl;
    BST c;
    cout << "If BST c == BST b: " << (c==b) << endl;
    c = b;
    cout << "If BST c == BST b after assigning c=b: " << (c==b) << endl;
    cout << "Address Test: " << c.kthSmallest(1) << " | " << b.kthSmallest(1)  << endl;
    cout << "----" << endl;
    // defined Constructor with bool balanced _ TEST:
    cout << "defined Constructor with bool balanced _ TEST:" << endl;
    BST d(arrayOfNodes, numberOfNodes, true);
    for (int i =0; i < numberOfNodes; i++){
        cout << arrayOfNodes[i] << " ";
    }
    cout << endl;
    d.DisplayTreeHorizontally();

    //Load from file test:
    cout << "Load from file test:" << endl;
    string fileName = "test.txt";
    a.LoadTreeFromFile(fileName);
    a.DisplayTreeHorizontally();
    a.LevelOrderDisplay();

    delete[] arrayOfNodes;
    return 0;
}