#include "RoundRobinProceeScheduler.h"
#include <iostream>

using namespace std;

int main(){
    RoundRobinProcessScheduler r("process.txt");

    r.Process();
    r.ShowResults();
    return 0;
}