/*
    cre: Danny Oct/7
*/

#include "PriorityQueue.h"
#include "PriorityQueue.cpp" //This should not be here. However, without a proper setup, the program may not run if you don't include the cpp file.
#include <ctime>


int main(){

    srand(time(0));
 
    PriorityQueue lst(3);
 
    for (int i =0; i < 10; i++){
        lst.Enqueue();
    }
    
    lst.Process();

    //I did not test Dequeue() since it's a part of Process(), you can try testing it.
    
    return 0;
}