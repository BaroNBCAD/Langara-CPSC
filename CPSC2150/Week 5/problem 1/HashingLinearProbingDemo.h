/*
    From Danny:
        I add value INT_MIN to indicate the deleted elements.
        If we use 0s as deleted keys, we have to rehash() the table every time we delete a node.

        So:
        0 indicates the slot has never been used.
        INT_MIN indicates the slot was used, now it's available.
*/


#ifndef HASHINGLINEARPROBINGDEMO_H
#define HASHINGLINEARPROBINGDEMO_H
#include <iostream>
#include <functional>
using namespace std;
class HashingLinearProbingDemo{
private:
    int* hashTable;
    int hashTableSize;
    int numberOfKeys;
    double loadFactorThreshold; 
    const int jump = 1;
public:
    HashingLinearProbingDemo(){
        hashTable = nullptr;
        hashTableSize = 0;
        numberOfKeys = 0;
        loadFactorThreshold = 1.0;
    }

    HashingLinearProbingDemo(int size, double lft){
        hashTableSize = size;
        hashTable = new int[hashTableSize];
        for(int i = 0; i < hashTableSize; i++){
            hashTable[i] = 0;
        }
        numberOfKeys = 0;
        loadFactorThreshold = lft;
    }
    ~HashingLinearProbingDemo(){
        if (hashTable != nullptr)
            delete hashTable;
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

            if(hashTable[hashTableIndex] == 0 || hashTable[hashTableIndex] == INT_MIN){
                // no collision
                hashTable[hashTableIndex] = value;
            }
            else{
                // use linear probing to resolve collision
                hashTableIndex = (hashTableIndex+jump) % hashTableSize;
                while (hashTable[hashTableIndex] != 0 && hashTable[hashTableIndex] != INT_MIN)
                    hashTableIndex = (hashTableIndex+jump) % hashTableSize;
                hashTable[hashTableIndex] = value;
            }
            numberOfKeys++;
        }
        else{
            cout << value << " already exists!\n";
        }


    }

    void ReHash(){
        if (hashTable == nullptr){
            hashTableSize = 5;
            hashTable = new int[hashTableSize];
            for(int i = 0; i < hashTableSize; i++){
                hashTable[i] = 0;
            }
            return;
        }
        int newHashTableSize = hashTableSize*2;
        int* newHashTable = new int[newHashTableSize];
        for (int i = 0; i < newHashTableSize; i++){
            newHashTable[i] = 0;
        }

        for (int i = 0, j = 0; i < hashTableSize, j < numberOfKeys; i++){
            if (hashTable[i] != 0 && hashTable[i] != INT_MIN){
                j++;
                hash<int> builtInHashFunction;
                int hashCode = builtInHashFunction(hashTable[i]);
                int hashTableIndex = hashCode % newHashTableSize;

                if(newHashTable[hashTableIndex] == 0){
                    newHashTable[hashTableIndex] = hashTable[i];
                }
                else{
                    hashTableIndex = (hashTableIndex+jump) % newHashTableSize;
                    while (newHashTable[hashTableIndex] != 0)
                        hashTableIndex = (hashTableIndex+jump) % newHashTableSize;
                    newHashTable[hashTableIndex] = hashTable[i];
                }
            }
        }

        delete hashTable; //hashTable can't be nullptr;
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

        if (hashTable[hashTableIndex] == 0) return false;
        else if (hashTable[hashTableIndex] == value) return true;

        int firstKeyIndex = hashTableIndex;
        hashTableIndex = (hashTableIndex+jump) % hashTableSize;
        while (hashTable[hashTableIndex] != 0 && hashTable[hashTableIndex] != value && hashTableIndex != firstKeyIndex){
            hashTableIndex = (hashTableIndex+jump) % hashTableSize;
        }
        return (hashTable[hashTableIndex] == value);
    }

    bool Delete(int value){
        //Using Search will make the complexity be 2*O(n)
        //Instead, I traverse the same way Search() does to find the value to remove.
        if (hashTable == nullptr || value == 0)
            return false;
        
        hash<int> builtInHashFunction;
        int hashCode = builtInHashFunction(value);
        int hashTableIndex = hashCode % hashTableSize;
        
        if (hashTable[hashTableIndex] == 0) return false;
        else if (hashTable[hashTableIndex] == value){
            hashTable[hashTableIndex] = INT_MIN;
            numberOfKeys--;
            return true;
        }

        int firstKeyIndex = hashTableIndex;
        hashTableIndex = (hashTableIndex+jump) % hashTableSize;

        while (hashTable[hashTableIndex] != 0 && hashTable[hashTableIndex] != value && hashTableIndex != firstKeyIndex){
            hashTableIndex = (hashTableIndex+jump) % hashTableSize;
        }

        if (hashTable[hashTableIndex] == value){
            hashTable[hashTableIndex] = INT_MIN;
            numberOfKeys--;
            return true;
        }
        else{
            cout << "Does not exist" << endl;
            return false;
        }
    }

    void Display(){
        cout << "----- TABLE -----" << endl;
        for(int i = 0; i < hashTableSize; i++){
            cout << "[" << i << "]: ";
            if (hashTable[i] != 0 && hashTable[i] != INT_MIN)
                cout << hashTable[i] << endl;
            else
                cout << "-" << endl;
        }
        cout << "-----------------" << endl;
        cout << "Current table size: " << hashTableSize << endl;
        cout << "Number of Keys: " << numberOfKeys << endl;
        cout << "Current Load Factor: " << (numberOfKeys*1.0)/hashTableSize << endl;
        cout << "Given Load Factor: " << loadFactorThreshold << endl;
        return;
    }

};
#endif
