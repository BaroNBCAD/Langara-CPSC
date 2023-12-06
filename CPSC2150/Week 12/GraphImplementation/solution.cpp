#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

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



int main() {

    Graph g("distances.txt");

    g.ShowLocationInfo();

    string source, destination;
    // User input for source and destination locations
    cout << "Enter the source location: ";
    cin >> source;
    cout << "Enter destination location(s), separated by commas if more than one destination: ";
    cin >> destination;

    vector<string> destinations;

    // check if there are multiple destinations
    if(destination.find(',') != string::npos){
        // multiple destinations
        destinations = Split(destination, ',');
        if(!g.LocationExists(source)){
            cout << "Invalid location." << endl;
            return 0;
        }
        for(string dest : destinations){
            if(!g.LocationExists(dest)){
                cout << "Invalid location." << endl;
                return 0;
            }
        }

        destinations.insert(destinations.begin(), source);
    }
    else{
        // single destination
        if(!g.LocationExists(source) || !g.LocationExists(destination)){
            cout << "Invalid location." << endl;
            return 0;
        }

        destinations.push_back(source);
        destinations.push_back(destination);
    }

    cout << "Locations are valid" << endl;

    if(g.FindShortestRoutes(destinations)){
        g.ShowShortestRoutes();
    }

    return 0;
}
