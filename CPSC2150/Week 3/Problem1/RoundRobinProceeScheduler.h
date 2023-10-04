#ifndef ROUNDROBINPROCESCHEDULER_H_
#define ROUNDROBINPROCESCHEDULER_H_

#include "CircularList.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Results{
    int processId;
    int turnAroundTime;
};

class RoundRobinProcessScheduler{
private:
    int timeQuantum;
    CircularLinkedList processTimes;
    vector<Results> results;
public:
    RoundRobinProcessScheduler(){
        timeQuantum = 0;
    }

    RoundRobinProcessScheduler(string fileName){
        LoadFromFile(fileName);
    }

    void LoadFromFile(string fileName){
        ifstream file(fileName);
        if(file.is_open()){
            string line;
            getline(file, line);
            timeQuantum = stoi(line);
            getline(file, line);
            int id = 1;
            string processTime = "";
            for(int i = 0; i < line.size(); i++){
                //cout << line[i] << endl;
                if(i != line.size() - 1 && line[i] != ','){
                    processTime += line[i];
                }
                else if(i != line.size() - 1 && line[i] == ','){
                    processTimes.insert(id, stoi(processTime));
                    processTime = "";
                    id++;
                }
                else if(i == line.size() - 1){
                    processTime += line[i];
                    processTimes.insert(id, stoi(processTime));
                }
            }
            file.close();            
        }
        else{
            cout << "File not found" << endl;
        }
    }

    void Process(){
        if(!processTimes.isEmpty()){
            Node* current = processTimes.getLast();
            current = current->next; // move to first process to have joined the list
            int timeElapsed = 0; // track time elapsed
            while(!processTimes.isEmpty()){
                if(current){
                    if(current->data > timeQuantum){
                        timeElapsed += timeQuantum;
                        current->data -= timeQuantum;
                        current = current->next;
                    }
                    else{
                        timeElapsed += current->data;
                        current->data = 0;
                        Results result = {current->id, timeElapsed};
                        results.push_back(result);
                        processTimes.deleteNode(0);
                        current = current->next;
                    }
                }
                else{
                    cout << "current is null" << endl;
                }
            }
        }
        else{
            cout << "No processes to schedule" << endl;
        }
    }

    void ShowResults(){
        double turnAroundtimes = 0;
        for(int i = 0; i < results.size(); i++){
            cout << "Process " << results[i].processId << " completed at " << results[i].turnAroundTime << endl;
            turnAroundtimes += results[i].turnAroundTime;
        }
        cout << "Average turn around time: " << fixed << setprecision(2) << turnAroundtimes / results.size() << endl;
    }
    
};


#endif