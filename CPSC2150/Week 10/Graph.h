#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

    void DFS(int v1, int v2, vector<bool> &visited, vector<int> &path, vector<vector<int>> &allPaths)
    {
        // mark v1 as visited
        visited[v1] = true;
        path.push_back(v1);

        if (v1 == v2)
        {
            return;
        }
        int size = path.size();
        // visit all neighbors of v1
        for (int i = 0; i < adjacencyList[v1].size(); i++)
        {
            if (!visited[adjacencyList[v1][i]])
            {
                DFS(adjacencyList[v1][i], v2, visited, path, allPaths);
                if (visited[v2])
                {
                    // if we have reached destination then add current path to allPaths and continue search
                    allPaths.push_back(path);
                    visited[v2] = false; // continue looking for other paths to destination, in case there are more
                }

                path.resize(size); // reset path
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

    void SolveMaze(int startRow, int startCol, int endRow, int endCol)
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
        vector<int> path;
        vector<vector<int>> allPaths;
        DFS(start, end, visited, path, allPaths);
        if (allPaths.size() > 0)
        {
            cout << "Following path(s) exist from row " << startRow << ", col " << startCol << " to row " << endRow << ", col " << endCol << ".\n";
            for (int p = 0; p < allPaths.size(); p++)
            {
                cout << "Path " << p << ":\n";
                ShowPath(start, end, allPaths[p]);
            }
        }
        else
        {
            cout << "No path exists from row " << startRow << ", col " << startCol << " to row " << endRow << ", col " << endCol << ".\n";
        }
    }
};

#endif