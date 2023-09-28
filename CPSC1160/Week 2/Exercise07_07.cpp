#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void Clear(int* arr, int arrLen){
    for(int i = 0; i < arrLen; i++){
        arr[i] = 0;
    }
}

int main() {
    srand(time(0));
    int length = 10;
    int* counts = new int[length];

    Clear(counts,length);

    for (int i = 0; i < 100; i++) {
      int value = (int)(rand() % length);
      counts[value]++;
    }

    for (int i = 0; i < length; i++) {
      cout << "Count for " << i << " is " << counts[i] << endl;
    }

    return 0;
}
