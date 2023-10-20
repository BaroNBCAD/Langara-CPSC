/*
    From Danny:
        
*/


#ifndef HASHINGSEPRATECHAINING_H
#define HASHINGSEPRATECHAINING_H
#include <iostream>
#include <functional>
#include "SkipList.h"
using namespace std;
class HashingSeparateChaining{
private:
    SkipList** hashTable;
    int hashTableSize;
    int numberOfKeys;
    double loadFactorThreshold; 
    int lvl = 3;
public:
    HashingSeparateChaining(){
        hashTable = nullptr;
        hashTableSize = 0;
        numberOfKeys = 0;
        loadFactorThreshold = 1.0;
    }

    HashingSeparateChaining(int size, double lft){
        hashTableSize = size;
        hashTable = new SkipList*[hashTableSize];
        for(int i = 0; i < hashTableSize; i++){
            hashTable[i] = new SkipList(lvl);
        }
        numberOfKeys = 0;
        loadFactorThreshold = lft;
    }

    HashingSeparateChaining(int size, double lft, int level){
        hashTableSize = size;
        lvl = level;
        hashTable = new SkipList*[hashTableSize];
        for(int i = 0; i < hashTableSize; i++){
            hashTable[i] = new SkipList(lvl);
        }
        numberOfKeys = 0;
        loadFactorThreshold = lft;
    }

    ~HashingSeparateChaining(){
        if (hashTable != nullptr){
            for(int i = 0; i < hashTableSize; i++){
                delete hashTable[i]; //This will trigger the SkipList destructor.
                hashTable[i] = nullptr;
            }
            delete[] hashTable;
            hashTable = nullptr;
        }
    }

    void Insert(int value){
        if(value == 0){
            cout << "0 not allowed\n";
            return;
        }
        if(!Search(value)){
            double currentLoadFactor = (double)(numberOfKeys + 1) / hashTableSize;
            if(currentLoadFactor > loadFactorThreshold){
                ReHash();
            }
            hash<int> builtInHashFunction;
            int hashCode = builtInHashFunction(value);
            int hashTableIndex = hashCode % hashTableSize;
            //Collision is solved by adding the node to the list.
            hashTable[hashTableIndex]->InsertElement(value);
            numberOfKeys++;
        }
        // else{
        //     cout << value << " already exists!\n";
        // }
    }

    void ReHash(){
        if (hashTable == nullptr){
            hashTableSize = 5;
            hashTable = new SkipList*[hashTableSize];
            for(int i = 0; i < hashTableSize; i++){
                hashTable[i] = new SkipList(lvl);
            }
            return;
        }
        int newHashTableSize = hashTableSize*2;
        SkipList** newHashTable = new SkipList*[newHashTableSize];
        for (int i = 0; i < newHashTableSize; i++){
            newHashTable[i] = new SkipList(lvl);
        }

        for (int i = 0, j = 0; i < hashTableSize, j < numberOfKeys; i++){
            Node* current = hashTable[i]->head->next[0];
            while (current != hashTable[i]->tail){
                j++;
                hash<int> builtInHashFunction;
                int hashCode = builtInHashFunction(current->value);
                int hashTableIndex = hashCode % newHashTableSize;
                newHashTable[hashTableIndex]->InsertElement(current->value);
                current = current->next[0];
            }
        }

        for(int i = 0; i < hashTableSize; i++){
            delete hashTable[i];
            hashTable[i] = nullptr;
        }
        delete[] hashTable;
        hashTable = newHashTable;
        hashTableSize = newHashTableSize;
        return;
    }

    bool Search(int value){
        if (hashTable == nullptr || value == 0)
            return false;

        hash<int> builtInHashFunction;
        int hashCode = builtInHashFunction(value);
        int hashTableIndex = hashCode % hashTableSize;
        return (hashTable[hashTableIndex]->Search(value));
    }

    bool Delete(int value){
        if (hashTable == nullptr || value == 0) //using search() here is inefficient.
            return false;
        
        hash<int> builtInHashFunction;
        int hashCode = builtInHashFunction(value);
        int hashTableIndex = hashCode % hashTableSize;
        if (hashTable[hashTableIndex]->Delete(value)){
            numberOfKeys--;
            return true;
        }
        else
            return false;
    }

    void Display(){
        cout << "----- TABLE -----" << endl;
        for(int i = 0; i < hashTableSize; i++){
            cout << "[" << i << "]: ";
            //ONLY SHOW THE LEVEL 0 SINCE LEVELS GREATER THAN 0 ARE ONLY MEANT TO BE USED BACK-END
            //SWITCH EITHER SHOWING THE WHOLE LIST, OR JUST SHOWING THE FIRST LEVEL.
            if (hashTable[i]->head->next[0] != hashTable[i]->tail)
                // hashTable[i]->ShowForward();
                hashTable[i]->ShowFirstLvl();
            else
                cout << "-" << endl;
        }
        cout << "-----------------" << endl;
        cout << "Current table size: " << hashTableSize << endl;
        cout << "Number of Keys: " << numberOfKeys << endl;
        cout << "Current Load Factor: " << loadFactorThreshold << endl;
        return;
    }

};
#endif