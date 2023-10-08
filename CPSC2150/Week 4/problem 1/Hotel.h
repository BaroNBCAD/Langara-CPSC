/*
    cre: Danny Oct/7
*/

#ifndef HOTEL_H
#define HOTEL_H
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

/*
    cre: Danny
    Room to improve: we do not use 2^0 (first digit of room).
*/
class Hotel{
    
    private:
        unsigned long long rooms;
    public:
        Hotel();

        bool CheckAvailability(int);
        void BookRoom(int);
        void CheckOut(int);
        void ShowRooms();
};

#endif
