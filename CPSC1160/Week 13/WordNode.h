#ifndef WORDNODE_H
#define WORDNODE_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "CharacterNode.h"

using namespace std;

class WordNode{
public:
    CharacterNode* firstCharacter; // pointer to first character in current word
    CharacterNode* lastCharacter; // pointer to last character in current word
    WordNode* next; // pointer to next word
    WordNode* prev; // pointer to previous word

    WordNode(){
        firstCharacter = nullptr;
        lastCharacter = nullptr;
        next = nullptr;
        prev = nullptr;
    }

    ~WordNode(){
        Clear();
    }

    WordNode(const WordNode& source){
        firstCharacter = nullptr;
        lastCharacter = nullptr;
        next = nullptr;
        prev = nullptr;
        Copy(source);
    }

    /**
     * @brief constructs a word from a string
     * @param word string to construct the word from
     */
    WordNode(const string& word){
        firstCharacter = nullptr;
        lastCharacter = nullptr;
        next = nullptr;
        prev = nullptr;
        for(int i = 0; i < word.length(); i++){
            CharacterNode* newCharacter = new CharacterNode(word[i]);
            AddCharacter(newCharacter);
        }
    }

    /**
     * @brief deallocates memory for all characters in the word
     */
    void Clear(){
        while (firstCharacter!=nullptr){
            CharacterNode* delNode= firstCharacter;
            firstCharacter = firstCharacter->next;
            delete delNode;
            delNode = nullptr;
        }
        lastCharacter=nullptr;
    }

    /**
     * @brief copies the contents of another word
     * @param source word to copy from
     */
    void Copy(const WordNode& source){
        CharacterNode* temp = source.firstCharacter;
        while(temp != nullptr){
            CharacterNode* newCharacter = new CharacterNode(temp->character);
            AddCharacter(newCharacter);
            temp = temp->next;
        }
    }

    bool IsEmpty(){
        return firstCharacter == nullptr;
    }

    // Assume c points to a valid character
    // Add c as the last character in the word
    // if the word is empty, c becomes the first and last character
    void AddCharacter(CharacterNode* c){
        if(IsEmpty()){
            firstCharacter = c;
            lastCharacter = c;
        }
        else{
            lastCharacter->next = c;
            c->prev = lastCharacter;
            lastCharacter = c;
        }
    }

    /**
     * @brief counts the total number of characters in the word
     * @return total number of characters in the word
     */
    int CountCharacters() const{
        return CountCharacters(firstCharacter);
    }

    int CountCharacters(const CharacterNode* c) const{
        if (!c){    //if c is nullptr then return 0
            return 0;
        }// if not, return 1 + the next call.
        return 1 + CountCharacters(c->next);
    }

    /**
     * @brief copies the contents of another word
     * @param source word to copy from
     * @return reference to the current word
     */
    WordNode& operator=(const WordNode& source){
        Clear();
        Copy(source);
        return *this;
    }

    /**
     * @brief returns the character at the specified index, if the index is invalid, prints an error message and returns null character
     * @param index index of the character to return
     * @return character at the specified index
     */
    char operator[](int index){
        if (index < 0 || index >= CountCharacters()){
            cout << "Invalid index. returning null" << endl;
            return 0;
        }
        CharacterNode* temp = firstCharacter;
        while (index-- > 0){
            temp=temp->next;
        };
        return temp->character;
    }

    /**
     * @brief compares the contents of the WordNode object with a string, case sensitive
     * @param word string to compare with
     * @return true if the contents of the two are the same, false otherwise
     */
    bool operator==(const string& word){
        if (CountCharacters() != word.size()) return false;
        CharacterNode* temp = firstCharacter;
        int index = 0;
        while (temp){ //while temp != nullptr
            if (temp->character != word[index])
                return false;
            index++;
            temp = temp->next;
        }
        return true;
    }

    /**
     * @brief compares the contents of the WordNode object with a string, case sensitive
     * @param word string to compare with
     * @return true if the contents of the two are not the same, false otherwise
     */
    bool operator!=(const string& word){
        return !(*this == word);
    }
};

#endif