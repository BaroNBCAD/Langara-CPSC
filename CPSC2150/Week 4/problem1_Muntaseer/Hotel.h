#ifndef HOTEL_H
#define HOTEL_H
#include <iostream>
#include <cmath>
using namespace std;

class Hotel{
private:
    unsigned long long int rooms;
public:
    Hotel(){
        rooms = 0; // all rooms are available for booking
    }

    void BookRoom(int roomNumber, unsigned long long int bitMask = 0){
        if(IsRoomAvailable(roomNumber, bitMask)){
            rooms |= bitMask;
        }
        else{
            cout << "Room " << roomNumber << " is not available.\n";
        }
    }

    void CancelRoom(int roomNumber, unsigned long long int bitMask = 0){
        if(!IsRoomAvailable(roomNumber, bitMask)){
            rooms &= (~bitMask);
        }
        else{
            cout << "Room " << roomNumber << " is not booked. Cannot cancel.\n";
        }
    }

    void ShowRooms(){
        cout << "Room Status: \n";
        int count = 0;
        unsigned long long int lastRoom = 1LL << 60;
        for(unsigned long long int currentRoom = 2; currentRoom <= lastRoom; currentRoom <<= 1){
            int roomIndex = log2(currentRoom);
            if(IsRoomAvailable(roomIndex, currentRoom)){
                cout << roomIndex << ": Available.\n";
                Increment(count);
            }
            else{
                cout << roomIndex << ": Not available.\n";
            }
        }
        cout << "Total available rooms = " << count << ", unavailable rooms = " << 60 - count << endl;
    }

private:
    bool IsRoomAvailable(int roomNumber, unsigned long long int &bitMask){
        if(roomNumber > 60 || roomNumber < 1){
            cout << "Invalid room number.\n";
            return false;
        }
        if(!bitMask){
            bitMask = 1LL << roomNumber;
        }
        return (rooms & bitMask) == 0;
    }

    void Increment(int &number){
        number = -(~number);
        return;
    }
};

#endif
