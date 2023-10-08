/*
    cre: Danny Oct/7
*/

#include "Hotel.h"

Hotel::Hotel(){
    rooms = 0;
}

bool Hotel::CheckAvailability(int roomNumber){
    unsigned long long room = pow(2, roomNumber);
    if ((rooms & room)==room)
        return false;
    else
        return true;
}

void Hotel::BookRoom(int roomNumber){
    if (CheckAvailability(roomNumber)){
        unsigned long long room = pow(2, roomNumber);
        rooms |= room;
        return;
    }
    else{
        cout << "The room has been reserved." << endl;
        return;
    }
}

void Hotel::CheckOut(int roomNumber){
    if (!CheckAvailability(roomNumber)){
        unsigned long long room = pow(2, roomNumber);
        rooms &= (~room);
        return;
    }
    else{
        cout << "The room has not been reserved to be checked out." << endl;
        return;
    }
}

void Hotel::ShowRooms(){
    unsigned long long counter = pow(2,60);
    int numberOfReserved = 0;
    int numberOfAvailable = 0;

    for (unsigned long long counter = 2; counter <= pow(2,60); counter=(counter<<1)){
        
        cout << "Room " << log2(counter);
        if ((rooms & counter)==counter){
            cout << ": reserved." << endl;
            numberOfReserved++;
        }
        else{
            cout << ": available." << endl;
            numberOfAvailable++;
        }
    }

    cout << "Reserved: " << numberOfReserved << endl;
    cout << "Available: " << numberOfAvailable << endl;
    return;
}
