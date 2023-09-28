#include <iostream>
#include <ctime>
using namespace std;

// Get a dice
int getDice()
{
  srand(time(0));
  int i1 = 1 + (rand() % 6);
  int i2 = 1 + (rand() % 6);

  cout << "You rolled " << i1 << " + " << i2 << " = " << (i1 + i2) << endl;

  return i1 + i2;
}

int main()
{
  int dice = getDice();
  if (dice == 7 || dice == 11)
  {
    cout << "You win" << endl;
    return 0;
  }
  else if (dice == 2 || dice == 3 || dice == 12)
  {
    cout << "You lose" << endl;
    return 0;
  }

  int point = dice;
  cout << "point is " << point << endl;
  do
  {
    dice = getDice();
  }
  while (dice != 7 && dice != point);

  if (dice == 7)
    cout << "You lose" << endl;
  else
    cout << "You win" << endl;
}

/** Determine if it is a leap year */
bool isLeapYear(int year)
{
  return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}
