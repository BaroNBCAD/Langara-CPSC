#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

/*

Based on 4 step process

*/
double f(int n, int k){
    if (k==0){
        return 0;
    }

    double smallSolution = (-pow(n,k)/(double)k) + (double)k/pow(n,k);
    double bigSolution = smallSolution + f(n, k-1);
    return bigSolution;
}

int main(){
    
    int n;
    int k;
    cout << "n: "; cin >> n;
    cout << "k: "; cin >> k;
    cout << "f(n, k): " << setprecision(2) << fixed << f(n, k) << endl;

    return 0;
}
