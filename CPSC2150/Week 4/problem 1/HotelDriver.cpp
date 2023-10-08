/*
    cre: Danny Oct/7
*/

#include "Hotel.cpp"

void displayMenu();
int getUserInput();
void Menu(int, Hotel&);

void Menu(int input, Hotel& hotel){
    if (input==0){
        cout << "Exiting the program";
        return;
    }

    if (input == 1){
        cout << "Showing Rooms"<<endl;
        hotel.ShowRooms();
    }
    else if (input == 2){
        cout <<"Booking Room" <<endl;
        int roomNumber = 0;
        do {
            cout << "Enter the room number: "; cin>>roomNumber;
        } while (roomNumber <=0 || roomNumber > 60);

        hotel.BookRoom(roomNumber);
    }
    else if (input == 3){
        cout <<"Checking Out" << endl;
        int roomNumber = 0;
        do {
            cout << "Enter the room number: "; cin>>roomNumber;
        } while (roomNumber <=0 || roomNumber > 60);
        hotel.CheckOut(roomNumber);
    }
    displayMenu();
    input = getUserInput();
    Menu(input, hotel);
    return;
}

int getUserInput(){
    int userInput = 0;
    do {
        cout << "Enter the input: "; cin >> userInput;
    } while (userInput <0 || userInput > 3);
    return userInput;
}

void displayMenu(){
    cout << "------------" << endl;
    cout << "0: Exit Program" << endl;
    cout << "1: Show Rooms" << endl;
    cout << "2: Book Room" << endl;
    cout << "3: Check Out" << endl;
    cout << "------------" << endl;
    return;
}

int main(){
    Hotel theHotel;
    displayMenu();
    int input = getUserInput();
    Menu(input, theHotel);
    return 0;
}
