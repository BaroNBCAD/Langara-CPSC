#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Vertex
{
public:
    int row;
    int col;
    bool isPath;

    Vertex()
    {
        row = -1;
        col = -1;
        isPath = false; // this will indicate an invalid vertex (not visitable)
    }

    Vertex(int r, int c)
    {
        row = r;
        col = c;
        isPath = true; // only storing path vertices and not walls
    }
};

class Graph
{
private:
    int mazeRows;
    int mazeCols;
    vector<Vertex> vertices;
    vector<vector<int>> adjacencyList;

    bool Valid(int row, int col)
    {
        return row >= 0 && row < mazeRows && col >= 0 && col < mazeCols;
    }

    int VertexIndex(int row, int col)
    {
        // our little hashfunction!
        return row * mazeCols + col; // should be unique for every row,col pair
    }

public:
    Graph()
    {
    }

    Graph(unsigned int adjacencyMatrix[4][4], int m, int n)
    {
        mazeRows = m;
        mazeCols = n;
        vertices.resize(mazeRows * mazeCols);      // treat this like a hashtable
        adjacencyList.resize(mazeRows * mazeCols); // treat this like a hashtable
        BuildGraph(adjacencyMatrix);
    }

    Graph(unsigned int **adjacencyMatrix, int m, int n)
    {
        mazeRows = m;
        mazeCols = n;
        vertices.resize(mazeRows * mazeCols);      // treat this like a hashtable
        adjacencyList.resize(mazeRows * mazeCols); // treat this like a hashtable
        BuildGraph(adjacencyMatrix);
    }

    void BuildGraph(unsigned int adjacencyMatrix[4][4])
    {
        for (int i = 0; i < mazeRows; i++)
        {
            for (int j = 0; j < mazeCols; j++)
            {
                if (adjacencyMatrix[i][j])
                {
                    int v = VertexIndex(i, j);
                    vertices[v] = Vertex(i, j);
                    if (Valid(i - 1, j) && adjacencyMatrix[i - 1][j])
                    {
                        adjacencyList[v].push_back(VertexIndex(i - 1, j));
                    }
                    if (Valid(i, j - 1) && adjacencyMatrix[i][j - 1])
                    {
                        adjacencyList[v].push_back(VertexIndex(i, j - 1));
                    }
                    if (Valid(i + 1, j) && adjacencyMatrix[i + 1][j])
                    {
                        adjacencyList[v].push_back(VertexIndex(i + 1, j));
                    }
                    if (Valid(i, j + 1) && adjacencyMatrix[i][j + 1])
                    {
                        adjacencyList[v].push_back(VertexIndex(i, j + 1));
                    }
                }
            }
        }
    }

    void BuildGraph(unsigned int **adjacencyMatrix)
    {
        for (int i = 0; i < mazeRows; i++)
        {
            for (int j = 0; j < mazeCols; j++)
            {
                if (adjacencyMatrix[i][j])
                {
                    int v = VertexIndex(i, j);
                    vertices[v] = Vertex(i, j);
                    if (Valid(i - 1, j) && adjacencyMatrix[i - 1][j])
                    {
                        adjacencyList[v].push_back(VertexIndex(i - 1, j));
                    }
                    if (Valid(i, j - 1) && adjacencyMatrix[i][j - 1])
                    {
                        adjacencyList[v].push_back(VertexIndex(i, j - 1));
                    }
                    if (Valid(i + 1, j) && adjacencyMatrix[i + 1][j])
                    {
                        adjacencyList[v].push_back(VertexIndex(i + 1, j));
                    }
                    if (Valid(i, j + 1) && adjacencyMatrix[i][j + 1])
                    {
                        adjacencyList[v].push_back(VertexIndex(i, j + 1));
                    }
                }
            }
        }
    }

    void ShowVertices()
    {
        cout << "Vertices: \n";
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i].isPath)
            {
                cout << "Vertex " << i << ": row " << vertices[i].row << ", col " << vertices[i].col << ".\n";
            }
        }
        cout << endl;
    }

    void ShowAdjacencyList()
    {
        cout << "Adjacency List:\n";
        for (int i = 0; i < adjacencyList.size(); i++)
        {
            if (vertices[i].isPath)
            {
                cout << "Vertex " << i << "(row " << vertices[i].row << ", col " << vertices[i].col << "): ";
                for (int j = 0; j < adjacencyList[i].size(); j++)
                {
                    cout << "row " << vertices[adjacencyList[i][j]].row << ", col " << vertices[adjacencyList[i][j]].col << "; ";
                }
                cout << endl;
            }
        }
    }

    void ShowPath(int v1, int v2, vector<int> path)
    {
        for (int i = 0; i < path.size(); i++)
        {
            cout << "" << vertices[path[i]].row << ", " << vertices[path[i]].col << endl;
        }
        cout << endl;
    }

    int lookForClosest(vector<bool> &visited, vector<int> &dist, int index){
        int minIndex = index;
        for (int i = 0; i < dist.size(); i++){
            // test if it's a vertex // test if visited // test if min
            if (vertices[i].isPath && !visited[i] && dist[i] < dist[minIndex]){
                minIndex = i;
            }
        }
        return minIndex;
    }

    void DFS(int v1, int v2, vector<bool> &visited, vector<int> &dist)
    {
        // mark v1 as visited
        visited[v1] = true;

        if (v1 == v2)
        {
            return;
        }

        int closestNeighbor = -1;

        for (int i = 0; i < adjacencyList[v1].size(); i++)
        {   
            if (!visited[adjacencyList[v1][i]])
            {
                dist[adjacencyList[v1][i]] = dist[v1] + 1;
                closestNeighbor = lookForClosest(visited, dist, adjacencyList[v1][i]);
            }
            if (closestNeighbor != -1)
                DFS(closestNeighbor, v2, visited, dist);
        }
        
    }

    void SolveMazeDijkstra(int startRow, int startCol, int endRow, int endCol)
    {
        if (!Valid(startRow, startCol) || !Valid(endRow, endCol))
        {
            cout << "Invalid start/end points!\n";
            return;
        }

        int start = VertexIndex(startRow, startCol);
        int end = VertexIndex(endRow, endCol);

        if (!vertices[start].isPath)
        {
            cout << "starting point is a wall!\n";
            return;
        }

        if (!vertices[end].isPath)
        {
            cout << "ending point is a wall!\n";
            return;
        }

        if (start == end)
        {
            cout << "start and end points are the same\n";
            return;
        }

        vector<bool> visited(vertices.size(), false);
        vector<int> dist(vertices.size(), INT_MAX);

        dist[start] = 0;
        DFS(start, end, visited, dist);

        for(int i = 0; i < dist.size(); i++){
            cout << "Vertex " << i << " distance " << dist[i] << endl;
        }
    }

};

#endif