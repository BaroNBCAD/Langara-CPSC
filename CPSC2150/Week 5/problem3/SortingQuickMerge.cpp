#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string MergeInOrder(string left, string right) {
	int lSize = left.length();
	int rSize = right.length();
    int i, j, k;
	string merged = "";
	i = j = k = 0;
	while (i < lSize && j < rSize) {
		if (left[i] <= right[j]) {
			merged = merged + left[i++];
		}
		else {
			merged = merged + right[j++];
		}
	}
	while (i < lSize) {
		merged = merged + left[i++];
	}
	while (j < rSize) {
		merged = merged + right[j++];
	}
	return merged;
}

string MergeSort(string& list){
    int size = list.length();
    if (size < 2)
        return list;
    int middlePoint = size/2;
    string left = list.substr(0, middlePoint);
    left = MergeSort(left);
    string right = list.substr(middlePoint);
    right = MergeSort(right);
    return MergeInOrder(left, right);
}