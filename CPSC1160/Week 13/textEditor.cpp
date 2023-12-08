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

    cout << "Showing stats:" << endl;
    paragraph.ShowStats();

    cout << "Counting \"is\" anywhere: " << paragraph.CountAnywhere("is") << endl;
    cout << "Counting the word \"is\": " << paragraph.CountWord("is") << endl;

    cout << "Replacing the word \"is\" with the word \"was\"." << endl;
    paragraph.ReplaceWord("is", "was");

    cout << "Showing forward:" << endl;
    paragraph.ShowForward();
    cout << "Showing backward:" << endl;
    paragraph.ShowBackward();

    cout << "Counting \"is\" anywhere: " << paragraph.CountAnywhere("is") << endl;
    cout << "Counting the word \"is\": " << paragraph.CountWord("is") << endl;
    cout << endl;
    // ///////////////////////////////////////
    cout << "Replacing the word \"is\" with the word \"was\". anywhere" << endl;
    paragraph.ReplaceAnywhere("is", "was");
     cout << "Showing forward:" << endl;
    paragraph.ShowForward();
    cout << "Showing backward:" << endl;
    paragraph.ShowBackward();
    cout << "Counting \"is\" anywhere: " << paragraph.CountAnywhere("is") << endl;
    cout << "Counting the word \"is\": " << paragraph.CountWord("is") << endl;

    return 0;
}

/* EXPECTED OUTPUT

Original text:
Showing forward:
This is the first sentence of the paragraph.
This is the second sentence of the paragraph.
This is the last sentence of the paragraph.

Showing backward:
hpargarap eht fo ecnetnes tsal eht si sihT.
hpargarap eht fo ecnetnes dnoces eht si sihT.
hpargarap eht fo ecnetnes tsrif eht si sihT.

Showing stats:
Number of sentences: 3
Number of words: 24
Number of characters: 108
Counting "is" anywhere: 6
Counting the word "is": 3
Replacing the word "is" with the word "was".
Showing forward:
This was the first sentence of the paragraph.
This was the second sentence of the paragraph.
This was the last sentence of the paragraph.

Showing backward:
hpargarap eht fo ecnetnes tsal eht saw sihT.
hpargarap eht fo ecnetnes dnoces eht saw sihT.
hpargarap eht fo ecnetnes tsrif eht saw sihT.

Counting "is" anywhere: 3
Counting the word "is": 0

*/

