#include <iostream>
#include "Graph.h"


int main(){
    unsigned int maze[4][4] = { {1,1,1,0},
                                {1,1,0,1},
                                {1,0,0,1},
                                {1,1,1,1}
                              };

    /**
     * @brief Given a maze (n x n 2D array of unsigned ints) where paths 
     * are marked with non-zero numbers and walls are 
     * marked with zeroes; output true/1 if there exists 
     * a path from the top-left corner (row 0, column 0) to the 
     * bottom-right corner (row n-1, column n-1) of the maze; if no path 
     * exists then output false/0.
     * 
     * Allowed movements through the maze: up (cell above the current cell), 
     * down (cell below the current cell), left (cell to the left of the 
     * current cell), right (cell to the right of the current cell).
     * 
     * ****NO diagonal movements are allowed****
     * 
     * 
     * In the maze shown above (4 x 4) there are 2 such paths.
     * 
     * If the top-left corner cell contains a zero in any maze then there 
     * can be no paths in that maze. 
     * 
     * Formulate the problem as a graph (vertices, edges).
     * Use graph algorithms (bfs, dfs) to solve the problem.
     * 
     * Thoroughly test your code - generate random mazes to validate your 
     * code. Try other values for n. You may limit your tests to unsigned 
     * int type square 2d arrays.
     * 
     * Feel free to use any Graph related code provided on D2L. 
     */

    Graph a = Graph(maze, 4);

    a.ShowVertices();
    cout << endl;
    a.ShowAdjacencyList();
    cout << endl;
    cout << a.Path() << endl;
    return 0;
}