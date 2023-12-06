#include <iostream>
#include <string>
#include "Text.h"

using namespace std;

int main(){
    Text paragraph("This is the first sentence of the paragraph. This is the second sentence of the paragraph. This is the last sentence of the paragraph.");

    cout << "Original text:" << endl;
    cout << "Showing forward:" << endl;
    paragraph.ShowForward();

    cout << "Showing backward:" << endl;
    paragraph.ShowBackward();
    
/**
 * Expected output:
Original text:
Showing forward:
This is the first sentence of the paragraph.
This is the second sentence of the paragraph.
This is the last sentence of the paragraph.

Showing backward:
hpargarap eht fo ecnetnes tsal eht si sihT.
hpargarap eht fo ecnetnes dnoces eht si sihT.
hpargarap eht fo ecnetnes tsrif eht si sihT.

 */

    return 0;
}

