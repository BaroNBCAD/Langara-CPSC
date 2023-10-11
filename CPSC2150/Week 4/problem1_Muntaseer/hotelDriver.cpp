#include "Hotel.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
    srand(time(0));
    Hotel h;

    int bookingCount = 0;
    for(int i = 1; i <= 60; i++){
        int coin = rand() % 2;
        if(coin == 1){
            cout << "Booking room " << i << endl;
            h.BookRoom(i);
            bookingCount++;
        }
    }

    h.ShowRooms();
    cout << bookingCount << " rooms booked during test.\n";

    int cancelCount = 0;
    for(int i = 1; i <= 60; i++){
        int coin = rand() % 2;
        if(coin == 0){
            cout << "Cancelling room " << i << endl;
            h.CancelRoom(i);
            cancelCount++;
        }
    }

    h.ShowRooms();
    cout << cancelCount << "*** rooms were cancelled.\n***Some Rooms that we tried to cancel may not have been booked in the first place. Check both lists above to verify!\n";


    return 0;
}
