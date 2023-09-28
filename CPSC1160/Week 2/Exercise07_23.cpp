#include <iostream>
using namespace std;

int main()
{
  // Declare a constant value for the number of lockers
  const int NUMBER_OF_LOCKER = 100;

  // Create an array to store the status of each array
  // The first student closes all lockers
  bool lockers[NUMBER_OF_LOCKER];
  for (int i = 0; i < NUMBER_OF_LOCKER; i++) {
    lockers[i] = false;
  }

  // Each student changes the lockers
  for (int j = 1; j <= NUMBER_OF_LOCKER; j++) {
    // Student Sj changes every jth clocker
    // starting from the lockers[j - 1].
    for (int i = j - 1; i < NUMBER_OF_LOCKER; i += j) {
      lockers[i] = !lockers[i];
    }
  }

  // Finds which one is open
  for (int i = 0; i < NUMBER_OF_LOCKER; i++) {
    if (lockers[i])
      cout << "Locker " << (i + 1) << " is open" << endl;
  }

  return 0;
}
