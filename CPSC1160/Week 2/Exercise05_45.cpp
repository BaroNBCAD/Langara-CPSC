#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
  const int COUNT = 10; // Total numbers
  double number = 0;
  double sum = 0; // Store the sum of the numbers
  double squareSum = 0; // Store the sum of the squares

  // Enter 10 numbers
  cout << "Enter ten numbers: ";

  for (int i = 0; i < COUNT; i++) {
    // Generate a new random number
    cin >> number;

    // Add the number to sum
    sum += number;

    // Add the square of the number to squareSum
    squareSum += pow(number * 1.0, 2); // Same as number*number;
  }

  // Find mean
  double mean = sum / COUNT;

  // Find standard deviation
  double deviation =
    sqrt((squareSum - sum * sum / COUNT) / (COUNT - 1));

  // Display result
  cout << "The mean is " << mean << endl;
  cout << "The standard deviation is " << deviation << endl;

  return 0;
}
