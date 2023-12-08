#ifndef CHARACTERNODE_H
#define CHARACTERNODE_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class CharacterNode{
public:
    char character; // current character
    CharacterNode* next; // pointer to next character
    CharacterNode* prev; // pointer to previous character

    CharacterNode(){
        character = ' '; // default character is a space
        next = nullptr;
        prev = nullptr;
    }

    CharacterNode(char c){
        character = c; // saving a character, data from the paragraph are finally stored at this level, rest of the nodes are just pointers to other nodes at a lower level
        next = nullptr;
        prev = nullptr;
    }

    /**
     * @brief copies the contents of another character
     * @param source character to copy from
     */
    CharacterNode(const CharacterNode& source){
        character = source.character;
        next = nullptr;
        prev = nullptr;
    }

    /**
     * @brief copies source.character to the this->character, does NOT copy the pointers
     * @param source character to copy from
     * @return reference to the current character
     */
    CharacterNode& operator=(const CharacterNode& source){
        character = source.character;
        return *this;
    }
};

#endif