#ifndef SENTENCENODE_H
#define SENTENCENODE_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "CharacterNode.h"
#include "WordNode.h"

using namespace std;

class SentenceNode{
public:
    WordNode* firstWord; // pointer to first word in current sentence
    WordNode* lastWord; // pointer to last word in current sentence
    SentenceNode* next; // pointer to next sentence
    SentenceNode* prev; // pointer to previous sentence

    SentenceNode(){
        firstWord = nullptr;
        lastWord = nullptr;
        next = nullptr;
        prev = nullptr;
    }

    ~SentenceNode(){
        Clear();
    }

    SentenceNode(const SentenceNode& source){
        firstWord = nullptr;
        lastWord = nullptr;
        next = nullptr;
        prev = nullptr;
        Copy(source);
    }

    /**
     * @brief deallocates memory for all words in the sentence
     */
    void Clear(){
        while (firstWord!=nullptr){
            WordNode* delNode= firstWord;
            firstWord = firstWord->next;
            delete delNode; // this will also call the destructor of WordNode.
            delNode = nullptr;
        }
        lastWord=nullptr;
    }

    /**
     * @brief copies the contents of another sentence
     * @param source sentence to copy from
     */
    void Copy(const SentenceNode& source){
        WordNode* temp = source.firstWord;
        while(temp != nullptr){
            WordNode* newWord = new WordNode(*temp);
            AddWord(newWord);
            temp = temp->next;
        }
    }

    bool IsEmpty(){
        return firstWord == nullptr;
    }

    // Assume w points to a valid word
    // Add w as the last word in the sentence
    // if the sentence is empty, w becomes the first and last word
    void AddWord(WordNode* w){
        if(IsEmpty()){
            firstWord = w;
            lastWord = w;
        }
        else{
            lastWord->next = w;
            w->prev = lastWord;
            lastWord = w;
        }
    }

    /**
     * @brief counts the total number of words in the sentence
     * @return total number of words in the sentence
     */
    int CountWords() const{
        return CountWords(firstWord);
    }

    int CountWords(const WordNode* w) const{
        if (!w){    //if c is nullptr then return 0
            return 0;
        }// if not, return 1 + the next call.
        return 1 + CountWords(w->next);
    }

    /**
     * @brief copies the contents of another sentence
     * @param source sentence to copy from
     * @return reference to the current sentence
     */
    SentenceNode& operator=(const SentenceNode& source){
        Clear();
        Copy(source);
        return *this;
    }

    /**
     * @brief returns the pointer to the word at the specified index, if the index is invalid, prints an error message and returns nullptr
     * @param index index of the word to return
     * @return pointer to word at the specified index
     */
    WordNode* operator[](int index){
        if (index < 0 || index >= CountWords()){
            cout << "Invalid index. returning null" << endl;
            return nullptr;
        }
        WordNode* temp = firstWord;
        while (index-- > 0){
            temp=temp->next;
        };
        return temp;
    }
};

#endif