/*
    Danny
    - roughly made -
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
    int matrix[4][4];
    int size;
    int dim; //dimensional

    void BuildACopy(unsigned int adjacencyMatrix[4][4], int n){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                matrix[i][j] = adjacencyMatrix[i][j];
            }
        }
    }

public:
    Graph(){
    }

    Graph(unsigned int maze[4][4], int n){
        dim = n;
        size = n*n;
        BuildACopy(maze, n);
        BuildVertices(n);
        BuildAdjacencyList(maze, n);
    }

    void BuildVertices(int n){
        for (int i =0; i < n*n; i++){
            vertices.push_back(i);
        }
    }

    void BuildAdjacencyList(unsigned int maze[4][4], int n){
        adjacencyList.resize(size);
        for (int row=0; row < n; row++){
            for (int col = 0; col < n; col++){
                if (maze[row][col]){
                    if (row-1>=0 && maze[row-1][col])
                        adjacencyList[n*row + col].push_back(n*(row-1)+col);
                    if (col-1>=0 && maze[row][col-1])
                        adjacencyList[n*row + col].push_back(n*row+col-1);
                    if (col+1 < n && maze[row][col+1])
                        adjacencyList[n*row + col].push_back(n*row+col+1);
                    if (row+1 < n && maze[row+1][col])
                        adjacencyList[n*row + col].push_back(n*(row+1)+col);
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
            if (adjacencyList[i].size() != 0){
                cout << "Vertex " << i << ": ";
                for (int j = 0; j < adjacencyList[i].size(); j++){
                    cout << adjacencyList[i][j] << ", ";
                }
                cout << endl;
            }
        }
    }

    int VertexCount(){
        // returns the number of vertices in the graph
        return vertices.size();
    }

    bool Path(){
        if (matrix[0][0]==0 || matrix[dim-1][dim-1] == 0) return 0;
        vector<bool> marked(size, false);
        stack<int> path;
        path.push(0);
        marked[0] = true;

        while (!path.empty()){
            int current = path.top();
            path.pop();
            for (int i = 0; i < adjacencyList[current].size(); i++){
                // cout << adjacencyList[current][i] << "--" << endl;
                if (!marked[adjacencyList[current][i]]){
                    path.push(adjacencyList[current][i]);
                    marked[adjacencyList[current][i]] = true;
                }
            }
            if (path.top() == (dim*dim-1))
                return true;
        }

        return false;
    }
};



#endif