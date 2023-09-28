#include <iostream>
using namespace std;

/** Return this number if it is a single digit, otherwise, return the sum of the two digits */
int getDigit(int number)
{
  return number % 10 + (number / 10 % 10);
}

/** Return sum of odd place digits in number */
int sumOfOddPlace(const string& cardNumber)
{
  int result = 0;

  for (int i = cardNumber.size() - 1; i >= 0; i = i - 2)
  {
    result += cardNumber[i] - '0';
  }

  return result;
}

/** Get the result from Step 2 */
int sumOfDoubleEvenPlace(const string& cardNumber)
{
  int result = 0;

  for (int i = cardNumber.size() - 2; i >= 0; i = i - 2)
  {
    result += getDigit((cardNumber[i] - '0') * 2);
  }

  return result;
}

/** Return true if substr is the prefix for cardNumber */
bool startsWith(const string& cardNumber, const string& substr) {
  if (cardNumber.size() < substr.size())
    return false;

  for (int i = 0; i < substr.size(); i++)
    if (cardNumber[i] != substr[i])
      return false;

  return true;
}

/** Return true if the card number is valid */
bool isValid(const string& cardNumber) {
  return (startsWith(cardNumber, "4") || startsWith(cardNumber, "5") ||
    startsWith(cardNumber, "6") || startsWith(cardNumber, "37")) &&
    (sumOfDoubleEvenPlace(cardNumber) + sumOfOddPlace(cardNumber)) % 10 == 0;
}

int main()
{
  cout << "Enter a credit card number as a string: ";
  char cardNumber[17]; // hold 16 characters with a null terminator
  cin >> cardNumber;

  if (isValid(cardNumber))
    cout << cardNumber << " is valid" << endl;
  else
    cout << cardNumber << " is invalid" << endl;

  return 0;
}
