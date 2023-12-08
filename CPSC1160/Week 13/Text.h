#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "CharacterNode.h"
#include "WordNode.h"
#include "SentenceNode.h"

using namespace std;

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

    ~Text(){
        Clear();
    }

    Text(const Text& source){
        firstSentence = nullptr;
        lastSentence = nullptr;
        Copy(source);
    }

    /**
     * @brief deallocates memory for all sentences in the text
     */
    void Clear(){
        while (firstSentence!=nullptr){
            SentenceNode* delNode= firstSentence;
            firstSentence = firstSentence->next;
            delete delNode; // this will also call the destructor of WordNode.
            delNode = nullptr;
        }
        lastSentence=nullptr;
    }

    /**
     * @brief copies the contents of another text
     * @param source text to copy from
     */
    void Copy(const Text& source){
        SentenceNode* temp = source.firstSentence;
        while(temp != nullptr){
            SentenceNode* newSentence = new SentenceNode(*temp);
            AddSentence(newSentence);
            temp = temp->next;
        }
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
                WordNode* newWord = new WordNode(words[w]);

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

    /**
     * @brief shows the following:
     * - total number of sentences in the text
     * - total number of words in the text
     * - total number of characters in the text
     */
    void ShowStats(){
        cout << "Number of sentences: " << CountSentences() << endl;
        int totalWords = 0;
        int totalCharacters = 0;
        SentenceNode* currentSentence = firstSentence;
        while(currentSentence != nullptr){
            totalWords += currentSentence->CountWords();
            WordNode* currentWord = currentSentence->firstWord;
            while(currentWord != nullptr){
                totalCharacters += currentWord->CountCharacters();
                currentWord = currentWord->next;
            }
            currentSentence = currentSentence->next;
        }
        cout << "Number of words: " << totalWords << endl;
        cout << "Number of characters: " << totalCharacters << endl;
    }

    /**
     * @brief counts the total number of sentences in the text
     * @return total number of sentences in the text
     */
    int CountSentences(){
        return CountSentences(firstSentence);
    }

    int CountSentences(const SentenceNode* c) const{
        if (!c){    //if c is nullptr then return 0
            return 0;
        }// if not, return 1 + the next call.
        return 1 + CountSentences(c->next);
    }

    /**
     * @brief copies the contents of another text
     * @param source text to copy from
     * @return reference to the current text
     */
    Text& operator=(const Text& source){
        Clear();
        Copy(source);
        return *this;
    }

    /**
     * @brief returns the pointer to the sentence at the specified index, if the index is invalid, prints an error message and returns nullptr
     * @param index index of the sentence to return
     * @return pointer to sentence at the specified index
     */
    SentenceNode* operator[](int index){
        if (index < 0 || index >= CountSentences()){
            cout << "Invalid index. returning null" << endl;
            return nullptr;
        }
        SentenceNode* temp = firstSentence;
        while (index-- > 0){
            temp=temp->next;
        };
        return temp;
    }

    /**
     * @brief returns true if any whole word in the text matches the specified word, false otherwise. case-sensitive.
     * @param  word word to search for
     * @return true if any whole word in the text matches the specified word, false otherwise
     */
    bool SearchWord(string word){
        SentenceNode* sentenceTemp = firstSentence;
        while (sentenceTemp){
            WordNode* wordTemp = sentenceTemp->firstWord;
            while (wordTemp){
                if (*wordTemp != word)
                    return false;
                wordTemp = wordTemp->next;
            }
            sentenceTemp = sentenceTemp->next;
        }
        return true;
    }

    /**
     * @brief returns true if string in txt appears anywhere within the text object (not just as a whole word); otherwise retuns false. case-sensitive.
     * @param  txt string to search for
     * @return true if string in txt appears anywhere within the text object (not just as a whole word); otherwise retuns false.
     */
    /*
        The reason I implemented it like this is because [txt] is a string, not a word. ie [txt] could be "a. Thi"
    */
    bool SearchAnywhere(string txt){
        string result = "";
        SentenceNode* sentenceTemp = firstSentence;
        while (sentenceTemp){
            WordNode* wordTemp = sentenceTemp->firstWord;
            while (wordTemp){
                CharacterNode* charTemp = wordTemp->firstCharacter;
                while (charTemp){
                    result += charTemp->character;
                    charTemp = charTemp->next;
                }
                if (wordTemp->next)
                    result+=" ";
                wordTemp = wordTemp->next;
            }
            result+=". ";
            sentenceTemp = sentenceTemp->next;
        }
        //  1
        return (result.find(txt) != -1);
        //  2
        // int size = txt.size();
        // for (int i=0; i < result.size(); i++){
        //     if(result.substr(i, size) == txt)
        //         return true;
        // }
        // return false;
    }

    bool IfWordExist(const string& s1, const string& s2){
        int size = s2.size();
        for (int i=0; i <= s1.size()-size; i++){
            if(s1.substr(i, size) == s2)
                return true;
        }
        return false;
    }
    
    int countWord(const string& s1, const string& s2){
        int count = 0;
        int size = s2.size();
        for (int i=0; i <= s1.size() - size; i++){
            // cout << "s1.substr(i, size): " << s1.substr(i, size) << endl;
            // cout << "s2: " << s2 << endl;
            if(s1.substr(i, size) == s2)
                count++;
        }
        return count;
    }
    /**
     * @brief returns the number of times the specified word appears as a whole word within the text object. case-sensitive.
     * @param  word string to search and count
     * @return number of times the specified word appears as a whole word within the text object
     */
    int CountWord(string word){
        SentenceNode* sentenceTemp = firstSentence;
        int count = 0;
        while (sentenceTemp){
            WordNode* wordTemp = sentenceTemp->firstWord;
            while(wordTemp){
                if (*wordTemp == word)
                    count++;
                wordTemp = wordTemp->next;
            }
            sentenceTemp=sentenceTemp->next;
        }
        return count;
    }

    /**
     * @brief returns the number of times the specified word appears anywhere within the text object (not just as a whole word). case-sensitive.
     * @param  word string to search and count
     * @return number of times the specified word appears anywhere within the text object (not just as a whole word)
     */
    /*
        This function performs differently from SearchAnyWhere because [word] here IS a word, not just a random string.
    */
    int CountAnywhere(string word){
        SentenceNode* sentenceTemp = firstSentence;
        string wordInString = "";
        int count = 0;
        while (sentenceTemp){
            WordNode* wordTemp = sentenceTemp->firstWord;
            while (wordTemp){
                CharacterNode* charTemp = wordTemp->firstCharacter;
                while (charTemp){
                    wordInString += charTemp->character;
                    charTemp = charTemp->next;
                }
                count = count + countWord(wordInString, word);
                wordInString = "";
                wordTemp = wordTemp->next;
            }
            
            sentenceTemp = sentenceTemp->next;
        }
        return count;
    }

    /**
     * @brief replaces each existence of oldWord (whole word and not a sub-string) with newWord. case-sensitive.
     * @param  oldWord string to search for and replace
     * @param  newWord string to replace oldWord with
     */
    void ReplaceWord(string oldWord, string newWord){
        WordNode* newWordNode = new WordNode(newWord);
        SentenceNode* sentenceTemp = firstSentence;
        while (sentenceTemp){
            WordNode* wordTemp = sentenceTemp->firstWord;
            while (wordTemp){
                if (*wordTemp == oldWord)
                    *wordTemp = *newWordNode;
                    //*wordTemp = newWord;    //This also works, altho I'm not sure how.
                wordTemp = wordTemp->next;
            }
            sentenceTemp = sentenceTemp->next;
        }
        delete newWordNode;
        return;
    }

    /**
     * @brief replaces each existence of oldText (not just as a whole word, could be a substring) with newText. case-sensitive.
     * @param  oldText string to search for and replace
     * @param  newText string to replace oldText with
     */

    /*
        Same implementation as SearchAnyWhere
    */
    void ReplaceAnywhere(string oldText, string newText){
        string result = "";
        SentenceNode* sentenceTemp = firstSentence;
        while (sentenceTemp){
            WordNode* wordTemp = sentenceTemp->firstWord;
            while (wordTemp){
                CharacterNode* charTemp = wordTemp->firstCharacter;
                while (charTemp){
                    result += charTemp->character;
                    charTemp = charTemp->next;
                }
                if (wordTemp->next)
                    result+=" ";
                wordTemp = wordTemp->next;
            }
            if (sentenceTemp->next)
                result+=". ";
            sentenceTemp = sentenceTemp->next;
        }
        int oldTextSize = oldText.size();
        for (int i=0; i <= result.size()-oldTextSize; i++){
            if(result.substr(i, oldTextSize) == oldText)
                result.replace(i, oldTextSize, newText);
        }
        Clear();
        ProcessParagraph(result);
        return;
    }
};

#endif
