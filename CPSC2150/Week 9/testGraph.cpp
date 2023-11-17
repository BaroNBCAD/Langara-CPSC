/*
    Danny
*/

#include <iostream>
#include "Graph.h"
using namespace std;

int main(){
    int testSize = 4;
    bool mat1[2][2] = { {0,1},
                        {1,0}
                        };

    bool mat2[4][4] = { {0,1,0,0},
                        {1,0,1,1},
                        {0,0,0,0},
                        {1,0,0,0}
                        };

    Graph a = Graph(mat2, 4);
    cout << "The graph is ";
    if (a.IsDirected()){
        cout << "directed." << endl;
    }
    else
        cout << "undirected." << endl;

    a.ShowVertices();
    cout << endl;
    a.ShowAdjacencyList();
    cout << endl;
    a.ShowEdgeList();
    cout << endl;
    
    for (int i = 0; i < testSize; i++){
        a.ShowNeighbors(i);
    }

    for (int i = 0; i < testSize; i++){
        cout << "Degree at " << i << " is: " << a.Degree(i) << endl;
    }

    a.ShowDegrees();

    cout << "HasEdge Test: " <<endl;

    cout << a.HasEdge(0,1) << endl;
    cout << a.HasEdge(0,2)<< endl;
    cout << a.HasEdge(0,3)<< endl;
    cout << a.HasEdge(3,0)<< endl;
    cout << "///////" <<endl;

    cout << "Path Test: 1 to 3" <<endl;
    cout << a.Path(1, 3) << endl;

    cout << "HasCycle(): ";
    if (a.HasCycle())
        cout << "yes." <<endl;
    else
        cout << "no." << endl;

    a.ShowCycles();

    return 0;
}
