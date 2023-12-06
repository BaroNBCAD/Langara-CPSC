#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

class Vertex
{
public:
    string name; // name of current location
    map<string, int> neighbors;     // Neighboring locations and their distances

    Vertex()
    {
        name = "n/a";
    }

    void AddNeighbor(string n, int d)
    {
        // add a neighbor (with name n and distance d) to neighbors
        
    }
};

struct Route
{
    vector<string> route; // route from source to destination
    int distance; // distance from source to destination
};

class Graph
{
private:
    map<string, Vertex> locations; // all cities and their neighbors (i.e. adjacencies) in the graph  
    vector<Route> routes; // if there are multiple destinations, store all routes here

public:
    Graph(){
    }

    Graph(string file = "distances.txt"){
        if(file == ""){
            return;
        }

        // Read road network data from a file
        ifstream inputFile(file);
        if (!inputFile) {
            cout << "Error: Unable to open input file." << endl;
            return;
        }

        // Parse the input file
        string sourceLocation, destLocation;
        int distance;
        while (inputFile >> sourceLocation >> destLocation >> distance) {
            locations[sourceLocation].name = sourceLocation;
            locations[destLocation].name = destLocation;
            locations[sourceLocation].neighbors[destLocation] = distance;
        }
        inputFile.close();
    }

    void ShowLocationInfo(){
        cout << "Locations:" << endl;
        for (const auto& pair : locations) {
            cout << pair.first << ": ";
            for (const auto& neighbor : pair.second.neighbors) {
                cout << neighbor.first << "(" << neighbor.second << "), ";
            }
            cout << endl;
        }        
    }

    // check if a location exists in the graph
    bool LocationExists(string location){
        return locations.find(location) != locations.end();
    }

    bool FindShortestRoute(string source, string destination){
        // check if source and destination exist in the graph
        if(!LocationExists(source) || !LocationExists(destination)){
            cout << "Invalid location." << endl;
            return false;
        }

        // check if source and destination are the same
        if(source == destination){
            cout << "Source and destination are the same." << endl;
            return false;
        }

        // reset route
        Route r;
        r.route.clear();
        r.distance = 0;

        // find shortest route

        // Custom comparator lambda function for priority queue
        auto comp = [](pair<string, int> left, pair<string, int> right) { 
            return left.second > right.second; 
        };

        map<string, int> distances; // shortest distances from source to each location
        map<string, string> previous; // previous location in the shortest route from source to each location
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(comp)> pq(comp);

        // initialize distances and previous
        for(auto& pair : locations){
            distances[pair.first] = INT_MAX;
            previous[pair.first] = "";
        }

        // set distance of source to 0
        distances[source] = 0;

        // add source to priority queue
        pq.push(make_pair(source, 0));

        // while priority queue is not empty
        while(!pq.empty()){
            // get the top element from the priority queue
            string u = pq.top().first;
            pq.pop();

            // for each neighbor of u
            for(auto& pair : locations[u].neighbors){
                string v = pair.first;
                int distance = pair.second;

                // if distance of u + distance < distance of v
                if(distances[u] + distance < distances[v]){
                    // update distance of v
                    distances[v] = distances[u] + distance;
                    // update previous of v
                    previous[v] = u;
                    // add v to priority queue
                    pq.push(make_pair(v, distances[v]));
                }
            }
        }

        // set route and distance
        string current = destination;
        while(current != ""){
            r.route.push_back(current);
            current = previous[current];
        }
        reverse(r.route.begin(), r.route.end());
        r.distance = distances[destination];

        // store the route
        routes.push_back(r);

        return true;
    }

    
    bool FindShortestRoutes(vector<string> destinations){
        // check if destinations exist in the graph
        for(string dest : destinations){
            if(!LocationExists(dest)){
                cout << "Invalid location." << endl;
                return false;
            }
        }

        // check if there are multiple destinations
        if(destinations.size() == 1){
            cout << "There is only one destination." << endl;
            return false;
        }

        for(int i = 0; i < destinations.size() - 1; i++){
            if(!FindShortestRoute(destinations[i], destinations[i + 1])){
                cout << "No route exists for the given locations." << endl;
                return false;
            }
        }

        return true;
    }


    void ShowShortestRoutes(){
        if(routes.empty()){
            cout << "No route found." << endl;
            return;
        }

        // show each route
        for(Route r : routes){
            cout << "\nShortest Route from " << r.route[0] << " to " << r.route[r.route.size() - 1] << ":" << endl;
            cout << "Distance: " << r.distance << " kilometers" << endl;
            cout << "Route: ";
            for (const string& location : r.route) {
                cout << location;
                if (location != r.route[r.route.size() - 1]) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }

};

#endif