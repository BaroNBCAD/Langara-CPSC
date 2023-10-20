#include <iostream>
#include <ctime>

using namespace std;
// 1
struct Point{
    int x;
    int y;
};

void Fill(Point* p, int n){
    if (n == 0) return;

    for (int i =0; i < n; i++){
        p[i].x = rand()%101;
        p[i].y = rand()%101;
    }
    return;
}

void Display(Point* p, int n){
    if (n == 0){
        cout << "The array is empty" << endl;
        return;
    }

    for (int i =0; i < n; i++){
        cout << "Point " << i << ": x:" << p[i].x <<", y: "<<p[i].y << endl;
    }
    return;
}

// 2
Point* MergeInOrder(Point* left, int lSize, Point* right, int rSize) {
	
    int i, j, k;

	Point* merged = new Point[lSize + rSize];
	i = j = k = 0;

	while (i < lSize && j < rSize) {
		if (left[i].x <= right[j].x) {
			merged[k++] = left[i++];
		}
		else {
			merged[k++] = right[j++];
		}
	}

	while (i < lSize) {
		merged[k++] = left[i++];
	}
	while (j < rSize) {
		merged[k++] = right[j++];
	}
	return merged;
}

void MergeSort(Point* p, int n){
    if (n < 2)
        return;
    int middlePoint = n/2;

    Point* left = new Point[middlePoint];
    for (int i =0; i < middlePoint; i++){
        left[i] = p[i];
    }    
    Point* right = new Point[n-middlePoint];
    for (int i=0; i < n-middlePoint; i++){
        right[i] = p[i+middlePoint];
    }

    MergeSort(left, middlePoint);
    MergeSort(right, n-middlePoint);
    delete p;
    p = MergeInOrder(left, middlePoint, right, n-middlePoint);
    delete left;
    delete right;    
    return;
}

// 3
void Shuffle(Point* p, int n){
    for (int i = 0; i < n; i++){
        int randNum = rand()%n; // get a random index
        while (randNum == i)
            randNum = rand()%n;
        Point temp = p[i];
        p[i] = p[randNum];
        p[randNum] = temp;
    }
}

// 4

int PlacePivot(Point*& p, int len) {
    int pivot, low, high;

    pivot = 0;
    low = 1;
    high = len - 1;

    while (low <= high) {
        if (p[low].y <= p[pivot].y) {
            low++;
        }
        else if (p[high].y > p[pivot].y) {
            high--;
        }
        else if(low <= high) {
            Point temp = p[low];
            p[low] = p[high];
            p[high] = temp;
        }
    }

    Point temp = p[pivot];
    p[pivot] = p[high];
    p[high] = temp;
    return high;
}

void QuickSortHelper(Point*& p, int size){
    if (size < 2)
        return;

    int pivot = PlacePivot(p, size);
    Point* left = new Point[pivot];
    for (int i =0; i < pivot; i++){
        left[i] = p[i];
    }
 
    Point* right = new Point[size - pivot - 1];
    for (int i =0; i < size-pivot-1; i++){
        right[i] = p[i+pivot+1];
    }
    QuickSortHelper(left, pivot);
    QuickSortHelper(right, size - pivot-1);
    for (int i =0; i < pivot; i++){
        p[i] = left[i];
    }
    for (int i =0; i < size-pivot-1; i++){
        p[i+pivot+1] = right[i];
    }
    delete left;
    delete right;
}


Point* QuickSort(Point* p, int n){
    if (n == 0){
        return nullptr;
    }
    if (n == 1){
        Point* result = new Point;
        *result = p[0];
        return result;
    }

    Point* result = new Point[n];
    for (int i =0; i < n; i++)
        result[i] = p[i];

    QuickSortHelper(result, n);
    return result;
}

// 5
void swap(int& a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
// arr[] = {2,3,5,1,3,4,7};

void display(int* arr, int size){
    for (int i =0; i < size; i++)
        cout << arr[i] << " - ";
    cout << endl;
}

void MergeInOrder(int* left, int lSize, int* right, int rSize) {
    for (int i =0; i < rSize; i++){
        int temp = i;
        for (int j= lSize-1; j >= 0; j--){
            if (right[temp] < left[j]){
                swap(right[temp], left[j]);
                temp--;
            }
            else
                break;
        }
        lSize++;
    }
}

int main(){
    srand(time(0));
    const int size = 7;
    // Point* points = new Point[size];
    // Fill(points, size);
    // Display(points, size);
    // cout << "---" << endl;
    // MergeSort(points, size);
    // Display(points, size);
    // cout << "---" << endl;
    // Shuffle(points, size);
    // Display(points, size);
    // cout << "---" << endl;
    // Point* quickSortTest = QuickSort(points, size);
    // Display(quickSortTest, size);
    // cout << "---" << endl;
    // delete points;
    // if (quickSortTest != nullptr)
    //     delete quickSortTest;

    //////////////////////////////////

    int arr[] = {2,3,5,1,3,4,7};
    display(arr, 7);
    MergeInOrder(arr, 3, arr+3, 4);
    display(arr, 7);
    return 0;
}