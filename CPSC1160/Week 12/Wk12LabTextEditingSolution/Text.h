#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <vector>

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
};

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
};

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
};

class Text{
private:
    SentenceNode* firstSentence; // pointer to first sentence in the paragraph
    SentenceNode* lastSentence; // pointer to last sentence in the paragraph

public:
    Text(){
        firstSentence = nullptr;
        lastSentence = nullptr;
    }

    Text(string p){
        firstSentence = nullptr;
        lastSentence = nullptr;
        ProcessParagraph(p);
    }

    bool IsEmpty(){
        return firstSentence == nullptr;
    }

    // Assume s points to a valid sentence
    // Add s as the last sentence in the paragraph
    // if the paragraph is empty, s becomes the first and last sentence
    void AddSentence(SentenceNode* s){
        if(IsEmpty()){
            firstSentence = s;
            lastSentence = s;
        }
        else{
            lastSentence->next = s;
            s->prev = lastSentence;
            lastSentence = s;
        }
    }

    // split a string into a vector of strings based on a split character
    // For example, Split("This is a sentence.", ' ') returns {"This", "is", "a", "sentence."}
    vector<string> Split(string s, char splitChar){
        vector<string> result;
        string current = "";
        for(int i = 0; i < s.length(); i++){
            if(s[i] == splitChar){
                if(current != ""){
                    result.push_back(current);
                    current = "";
                }
            }
            else{
                current += s[i];
            }
        }
        if(current != ""){
            result.push_back(current);
        }
        return result;
    }

    // Assume p contains a paragraph of text with sentences separated by periods. Each period is followed by a single space except the last.
    // Each sentence contains words separated by a single space with the last word followed by a period.
    // Each word contains characters.
    void ProcessParagraph(string p){
        // split p into sentences
        // for each sentence
        //      create a new SentenceNode named s
        //      split the sentence into words
        //      for each word
        //          create a new WordNode named w
        //          for each character
        //              create a new CharacterNode named c
        //              add c to w
        //          add w to s
        //      add s to the current Text object by calling AddSentence

        vector<string> sentences = Split(p, '.');
        for(int s = 0; s < sentences.size(); s++){
            SentenceNode* newSentence = new SentenceNode();

            vector<string> words = Split(sentences[s], ' ');
            for(int w = 0; w < words.size(); w++){
                WordNode* newWord = new WordNode();

                for(int c = 0; c < words[w].length(); c++){
                    CharacterNode* newCharacter = new CharacterNode(words[w][c]);
                    newWord->AddCharacter(newCharacter);
                }

                newSentence->AddWord(newWord);
            }

            AddSentence(newSentence);
        }
    }

    // display each sentence on a separate line from first to last
    // each sentence ends with a period
    //
    // display each word on the same line from first to last
    // each word ends with a single space except the last word
    //
    // display each character on the same line from first to last
    //
    // add the end of all sentences, display a new line 
    void ShowForward(){
        SentenceNode* currentSentence = firstSentence;
        while(currentSentence != nullptr){
            WordNode* currentWord = currentSentence->firstWord;
            while(currentWord != nullptr){
                CharacterNode* currentCharacter = currentWord->firstCharacter;
                while(currentCharacter != nullptr){
                    // complete from here
                    cout << currentCharacter->character;
                    currentCharacter = currentCharacter->next;
                }
                if(currentWord->next != nullptr){
                    cout << " ";
                }
                currentWord = currentWord->next;
            }
            cout << ".\n";
            currentSentence = currentSentence->next;
        }
        cout << endl;
    }

    // display each sentence on a separate line from last to first
    // each sentence ends with a period
    //
    // display each word on the same line from last to first
    // each word ends with a single space except the last word
    //
    // display each character on the same line from last to first
    //
    // add the end of all sentences, display a new line
    void ShowBackward(){
        SentenceNode* currentSentence = lastSentence;
        while(currentSentence != nullptr){
            WordNode* currentWord = currentSentence->lastWord;
            while(currentWord != nullptr){
                CharacterNode* currentCharacter = currentWord->lastCharacter;
                while(currentCharacter != nullptr){
                    // complete from here
                    cout << currentCharacter->character;
                    currentCharacter = currentCharacter->prev;
                }
                if(currentWord->prev != nullptr){
                    cout << " ";
                }
                currentWord = currentWord->prev;
            }
            cout << ".\n";
            currentSentence = currentSentence->prev;
        }
        cout << endl;
    }
};

#endif