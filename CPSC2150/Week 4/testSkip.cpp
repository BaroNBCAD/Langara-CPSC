#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SkipList.h"

using namespace std;

int main(){
    // srand(time(0));
 
    SkipList lst(3); // skiplist with maximum allowed level index
 
    lst.InsertElement(13);
    lst.InsertElement(7);
    lst.InsertElement(11);
    lst.InsertElement(1);
    lst.InsertElement(5);
    lst.InsertElement(19);

    lst.InsertElement(313);
    lst.InsertElement(37);
    lst.InsertElement(311);
    lst.InsertElement(31);
    lst.InsertElement(35);
    lst.InsertElement(319);

    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    cout<<"-----------------" << endl;
    lst.Delete();
    lst.ShowForward();
    lst.ShowBackward();
    
    // cout << "Removing 13" << endl;
    // lst.Delete(13);
    // lst.ShowForward();
    // lst.ShowBackward();

    // cout << "Removing 7" << endl;
    // lst.Delete(7);
    // lst.ShowForward();
    // lst.ShowBackward();

    // cout << "Removing 313" << endl;
    // lst.Delete(313);
    // lst.ShowForward();
    // lst.ShowBackward();

    // cout << "Removing 327" << endl;
    // lst.Delete(327);
    // lst.ShowForward();
    // lst.ShowBackward();

    // cout << "Removing 11" << endl;
    // lst.Delete(11);
    // lst.ShowForward();
    // lst.ShowBackward();

    // cout << "Removing 311" << endl;
    // lst.Delete(311);
    // lst.ShowForward();
    // lst.ShowBackward();

    return 0;
}