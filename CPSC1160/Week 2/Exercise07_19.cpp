#include <iostream>
using namespace std;

bool isSorted(int list[], int size)
{
  for (int i = 0; i < size - 1; i++) 
    if (list[i] > list[i + 1]) 
      return false;

  return true;
}
int main()
{
  const int MAX_SIZE = 80;

  // Enter values for list1
  cout << "Enter a list: ";
  int size;
  cin >> size;
  
  int list[MAX_SIZE];    
  for (int i = 0; i < size; i++) 
  cin >> list[i];

  if (isSorted(list, size))    
    cout << "The list is already sorted" << endl;
  else
	cout << "The list is not sorted" << endl;

  return 0;
}