#include <iostream>
#include <cmath>
using namespace std;

/** Function for computing mean of an array of double values */
double mean(double x[], int size)
{
  double sum = 0;

  for (int i = 0; i < size; i++)
    sum += x[i];

  return sum * 1.0 / size;
}

/** Function for computing mean of an array of int values */
double mean(int x[], int size)
{
  int sum = 0;

  for (int i = 0; i < size; i++)
    sum += x[i];

  return sum / size;
}

/** Function for computing deviation of double values */
double deviation(double x[], int size)
{
  double mean1 = mean(x, size);
  double squareSum = 0;

  for (int i = 0; i < size; i++)
  {
    squareSum += pow(x[i] - mean1, 2);
  }

  return sqrt(squareSum / (size - 1));
}

/** Function for computing deviation of int values */
double deviation(int x[], int size)
{
  double mean1 = mean(x, size);
  double squareSum = 0;

  for (int i = 0; i < size; i++)
  {
    squareSum += pow(x[i] - mean1, 2);
  }

  return sqrt(squareSum / (size - 1));
}

/** Function for printing array */
void printArray(double x[], int size)
{
  for (int i = 0; i < size; i++)
    cout << x[i] << " ";
  cout << endl;
}

int main()
{
  const int SIZE = 10;
  // Declare and create an array for 10 numbers
  double numbers[SIZE];

  cout << "Enter ten numbers: ";
  for (int i = 0; i < SIZE; i++)
  {
    cin >> numbers[i];
  }

  // Print numbers
  // printArray(numbers, 10);

  // Display mean and deviation
  cout << "The mean is " << mean(numbers, 10) << endl;
  cout << "The standard deviation is " << deviation(numbers, 10) << endl;

  return 0;
}
