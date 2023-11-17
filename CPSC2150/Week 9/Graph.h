/*
    Danny
    - roughly done -
    You all are welcome to look for bugs.
    It would help me and others!!
    Thank you.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Edge{
public:
    // assume u and v are two vertices 
    // vertices are zero-indexed
    int u;
    int v;

    Edge(){
        u = -1; // invalid vertex index
        v = -1; // invalid vertex index
    }

    Edge(int _u, int _v){
        u = _u;
        v = _v;
    }
};

class Graph{
private:
    vector<int> vertices;
    vector<vector<int>> adjacencyList;
    vector<Edge> edgeList;


    /// ADDED STUFF
    bool matrix[4][4];
    int size;
    bool isValidVertex(int v){
        if (v<0 || v > adjacencyList.size()){
            return false;
        }
        return true;
    }

    void BuildACopy(bool adjacencyMatrix[4][4], int n){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                matrix[i][j] = adjacencyMatrix[i][j];
            }
        }
    }

public:
    Graph(){
    }

    Graph(bool adjacencyMatrix[4][4], int n){
        // adjacencyMatrix has dimension n x n with zeroes along the main diagonal
        // assume row 0 is for vertex 0, row 1 is for vertex 1 and so on

        // TASKS: add methods to do the following:
        // build vertices, adjacencyList, edgeList using adjacencyMatrix.

        //optional
        size = n;
        BuildACopy(adjacencyMatrix, n);

        BuildVertices(n);
        BuildAdjacencyList(adjacencyMatrix, n);

        //optional
        BuildEdgeList(n);
    }

    void BuildVertices(int numberOfVertices){
        for (int i =0; i < numberOfVertices; i++){
            vertices.push_back(i);
        }
    }

    void BuildAdjacencyList(bool adjacencymatrix[4][4], int n){
        adjacencyList.resize(n);
        for (int vertex = 0; vertex < n; vertex++){
            for (int col = 0; col < n; col++){
                if (col == vertex){
                    continue;
                }
                if (adjacencymatrix[vertex][col]){
                    adjacencyList[vertex].push_back(col);
                }
            }
        }
    }

    //optional
    void BuildEdgeList(int n){
        // ASSUME THAT BUILDEDGELIST IS ONLY CALLED IN THE CONSTRUCTOR AND AFTER THE ADJACENCYLIST HAS BEEN BUILT
        if (!IsDirected()){
            for (int vertex = 0; vertex < n; vertex++){
                for (int adjacent = 0; adjacent < adjacencyList[vertex].size(); adjacent++){
                    if (adjacencyList[vertex][adjacent] > vertex){
                        Edge a(vertex, adjacencyList[vertex][adjacent]);
                        edgeList.push_back(a);
                    }
                }
            }
        }
        else{
            for (int vertex = 0; vertex < n; vertex++){
                for (int adjacent = 0; adjacent < adjacencyList[vertex].size(); adjacent++){
                    Edge a(vertex, adjacencyList[vertex][adjacent]);
                    edgeList.push_back(a);
                }
            }
        }
    }

    void ShowVertices(){
        cout << "Vertices: "; 
        for (int i =0; i < vertices.size()-1; i++){
            cout << vertices[i] << ", ";
        }
        cout << vertices[vertices.size()-1] << "." << endl;
    }

    void ShowAdjacencyList(){
        // display adjacency list
        cout << "Adjacency List\n";
        for (int i = 0; i < adjacencyList.size(); i++){
            cout << "Vertex " << i << ": ";
            for (int j = 0; j < adjacencyList[i].size(); j++){
                cout << adjacencyList[i][j] << ", ";
            }
            cout << endl;
        }
    }

    //optional
    void ShowEdgeList(){
        // display edge list
        cout << "Edge List\n";
        for (int i = 0; i < edgeList.size(); i++){
            cout << "Edge " << i << ": (" << edgeList[i].u << ", " << edgeList[i].v << ")\n";
        }
    }

    int VertexCount(){
        // returns the number of vertices in the graph
        return vertices.size();
    }

    int EdgeCount(){
        // returns the number of edges in the graph
        //1: adjacencyList/2 (only works with undirected graph)
        //2
        return edgeList.size();
    }

    void ShowNeighbors(int v){
        if (!isValidVertex(v)){
            cout << "Invalid input." << endl;
            return;
        }
        // display neighbors of vertex v
        cout << "Neighbors of vertex " << v << ": ";
        for (int j = 0; j < adjacencyList[v].size(); j++){
            cout << adjacencyList[v][j] << ", ";
        }
        cout << endl;
    }

    int Degree(int v){
        // return the degree of vertex v
        if (!isValidVertex(v)){
            cout << "Invalid input. Returning INT_MIN" << endl;
            return INT_MIN;
        }
        return adjacencyList[v].size();
    }

    bool IsDirected(){
        // returns true if the graph is directed; false otherwise
        for (int vertex = 0; vertex < size; vertex++){
            for (int col = 0; col < size; col++){
                if (col != vertex){ //prevent diagonal
                    if (matrix[col][vertex] != matrix[vertex][col])
                        return true;
                }
            }
        }
        return false;
    }

    void ShowDegrees(){
        // display degrees of all vertices
        cout << "Display degrees:\n";
        for (int vertex = 0; vertex < adjacencyList.size(); vertex++){
            cout << "Degree of vertex [" << vertex << "] is: " << adjacencyList[vertex].size() << endl;
        }
    }

    bool HasEdge(int v1, int v2){
        // returns true if there is an edge between vertices v1 n v2; false otherwise
        if (isValidVertex(v1) && isValidVertex(v2)){
            for (int vertexV1 = 0; vertexV1 < adjacencyList[v1].size() && adjacencyList[v1][vertexV1] <= v2; vertexV1++){
                if (adjacencyList[v1][vertexV1] == v2){
                    return true;
                }
            }
            for (int vertexV2 = 0; vertexV2 < adjacencyList[v2].size() && adjacencyList[v2][vertexV2] <= v1; vertexV2++){
                if (adjacencyList[v2][vertexV2] == v1){
                    return true;
                }
            }
            return false;            
        }
        else{
            cout << "Invalid vertices." << endl;
            return false;
        }
    }

    int Path(int v1, int v2){
        // returns the length of the path (number of edges) if there is a path from vertex v1 to vertex v2; otherwise returns 0
        // returns true if there is an edge between vertices v1 n v2; false otherwise
        if (isValidVertex(v1) && isValidVertex(v2)){
            if (v1 == v2) return 0;

            vector<int> marked(vertices.size(), false);
            stack<int> path;
            path.push(v1);
            marked[v1] = true;

            while (!path.empty()){
                int current = path.top();
                int i = 0;
                for (; i < adjacencyList[current].size() && marked[adjacencyList[current][i]]; i++);
                if (i != adjacencyList[current].size()){
                    path.push(adjacencyList[current][i]);
                    if (adjacencyList[current][i] == v2){
                        return path.size()-1;
                    }
                    marked[adjacencyList[current][i]] = true;
                }
                else{
                    path.pop();
                }
            }
            if (path.empty()){
                cout << "There's no path." << endl;
                return 0;
            }
        }
        else{
            cout << "Invalid vertices." << endl;
            return 0;
        }
    }

    bool checkCycle(int v, vector<bool>& marked, vector<bool>& recur)
    {
        if (!marked[v]) {
            marked[v] = true;
            recur[v] = true;
    
            int i = 0;
            for (int i = 0; i < adjacencyList[v].size(); i++) {
                if (!marked[adjacencyList[v][i]] && checkCycle(adjacencyList[v][i], marked, recur))
                    return true;
                else if (recur[adjacencyList[v][i]])
                    return true;
            }
        }
    
        // Remove the vertex from recursion stack
        recur[v] = false;
        return false;
    }

    /*
    
    DIRECTED GRAPH HASCYCLE
    cite: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/

    */
   
    bool HasCycle(){
        // return true if graph has a cycle (starting from a node we follow edges to return back to the same vertex); false otherwise
        vector<bool> marked(vertices.size(), false);
        vector<bool> recur(vertices.size(), false);
        for (int i =0; i < vertices.size(); i++){
            if (!marked[i]){
                if (checkCycle(i, marked, recur))
                    return true;
            }
        }
        return false;

    }

    stack<stack<int>> getPath(int v1, int v2){
        // returns the length of the path (number of edges) if there is a path from vertex v1 to vertex v2; otherwise returns 0
        // returns true if there is an edge between vertices v1 n v2; false otherwise
        stack<stack<int>> resultPaths;
        if (isValidVertex(v1) && isValidVertex(v2)){
            if (v1 == v2) return resultPaths;

            vector<bool> marked(vertices.size(), false);
            vector<bool> recur(vertices.size(), false);
            stack<int> path;
            path.push(v1);
            marked[v1] = true;

            while (!path.empty()){
                int current = path.top();

                int i = 0;

                for (; i < adjacencyList[current].size();){
                    if (marked[adjacencyList[current][i]]){
                        i++;
                    }
                    else if (!marked[adjacencyList[current][i]] && recur[current] && adjacencyList[current][i] == v2){
                        i++;
                    }
                    else
                        break;
                }

                if (i != adjacencyList[current].size()){
                    path.push(adjacencyList[current][i]);
                    marked[adjacencyList[current][i]] = true;
                    if (adjacencyList[current][i] == v2){
                        recur[current] = true;
                        resultPaths.push(path);
                        path.pop();
                        marked[adjacencyList[current][i]] = false;
                    }
                }
                else{
                    path.pop();
                }
            }
            if (path.empty()){
                return resultPaths;
            }
        }
        else{
            return resultPaths;
        }
    }

    void ShowCycles(){
        // displays all cycles (if any)
        // each cycle should begin and end with the same vertex
        cout << "Display cycles: " << endl;
        for (int i =0; i < vertices.size(); i++){
            cout << "Vertex " << i << endl;
            for (int j =0; j < adjacencyList[i].size(); j++){
                stack<stack<int>> paths = getPath(adjacencyList[i][j], i);
                if (!paths.empty()){
                    while (!paths.empty()){
                        stack<int> path = paths.top();
                        stack<int> reversePath;
                        paths.pop();
                        while (!path.empty()){
                            reversePath.push(path.top());
                            path.pop();
                        }
                        cout << i << " -> ";
                        while(reversePath.size() > 1){
                            cout << reversePath.top() << " -> ";
                            reversePath.pop();
                        }
                        cout << reversePath.top() << "." << endl;
                    }
                }
            }
            cout << " - - - " << endl;
        }
        return;
    }
    

};



#endif
