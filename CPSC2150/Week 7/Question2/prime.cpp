#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> Primes(int n) {
    if (n < 1)
        return vector<int>();
    
    const int limit = 16000;
    vector<int> result;
    int numAdded = 0;
    bool* nums = new bool[limit]();
    for (int i=2; i < limit; i++){
        if (!nums[i]){
            nums[i] = true;
            result.push_back(i);
            numAdded++;
            if (numAdded == n){
                delete[] nums;
                return result;
            }

            for (int j = i*i; j < limit; j+=i){
                nums[j] = true;
            }
        }
    }
    
    return result;
}

int main() {
    vector<int> result = Primes(100);
    for (int i =0; i < result.size(); i++){
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
