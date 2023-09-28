#include <iostream>
using namespace std;

int main()
{
  int size  =100;
  int* temp = new int[size];
  // Prompt the user to enter input
  cout << "Enter a year: ";
  int year;
  cin >> year;

  cout << "Enter the first day of the year: ";
  int firstDay;
  cin >> firstDay;

  int startDay = firstDay;
  int numberOfDaysInMonth = 0;

  // Display calendar for each month
  for (int month = 1; month <= 12; month++)
  {
    cout << "            ";

    // Display Calendar title
    switch (month)
    {
      case 1:
        cout << "January " << year << endl;
        numberOfDaysInMonth = 31;
      break;
      case 2:
        cout << "Feburary " << year << endl;
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
          numberOfDaysInMonth = 29;
        else
          numberOfDaysInMonth = 28;
      break;
      case 3:
        cout << "March " << year << endl;
        numberOfDaysInMonth = 31;
      break;
      case 4:
        cout << "April " << year << endl;
        numberOfDaysInMonth = 30;
      break;
      case 5:
        cout << "May " << year << endl;
        numberOfDaysInMonth = 31;
      break;
      case 6:
        cout << "June " << year << endl;
        numberOfDaysInMonth = 30;
      break;
      case 7:
        cout << "July " << year << endl;
        numberOfDaysInMonth = 31;
      break;
      case 8:
        cout << "August " << year << endl;
        numberOfDaysInMonth = 31;
      break;
      case 9:
        cout << "September " << year << endl;
        numberOfDaysInMonth = 30;
      break;
      case 10:
        cout << "October " << year << endl;
        numberOfDaysInMonth = 31;
      break;
      case 11:
        cout << "November " << year << endl;
        numberOfDaysInMonth = 30;
      break;
      case 12:
        cout << "December " << year << endl;
        numberOfDaysInMonth = 31;
      break;
    }

    cout << "-----------------------------" << endl;
    cout << " Sun Mon Tue Wed Thu Fri Sat" << endl;

    // Pad space before the first day of the month
    int i = 0;
    for (i = 0; i < startDay; i++)
      cout << "    ";

    for (i = 1; i <= numberOfDaysInMonth; i++)
    {
      if (i < 10)
        cout << "   " << i;
      else
        cout << "  " << i;

      if ((i + startDay) % 7 == 0)
        cout << endl;
    }

    cout << endl;
    cout << endl;

    // Get the start day for the next month
    startDay = (startDay + numberOfDaysInMonth) % 7;
  }

  return 0;
}
