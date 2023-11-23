/*
    Cre: Prof Muntaseer
*/
#include <iostream>
#include "Graph.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
  // SIMPLE TESTING
  // unsigned int maze[4][4] = { {1,1,1,1},
  //                             {0,1,0,1},
  //                             {0,1,0,1},
  //                             {0,1,1,1}
  //                           };

  // Graph g(maze, 4, 4);

  // g.ShowVertices();
  // g.ShowAdjacencyList();
  // g.SolveMaze(0,0,3,3);
  // g.SolveMaze(1,1,0,3);
  // g.SolveMaze(0,0,4,4);



  // // THOROUGH TESTING (COMMENT OUT THE ABOVE AND UNCOMMENT THE BELOW)

  srand(time(0));
  int mazeRows = rand() % 10 + 1;
  int mazeCols = rand() % 10 + 1;
  unsigned int **maze = new unsigned int *[mazeRows];
  cout << "THE MAZE:\n";
  for (int row = 0; row < mazeRows; row++)
  {
    maze[row] = new unsigned int[mazeCols];
    for (int col = 0; col < mazeCols; col++)
    {
      maze[row][col] = rand() % 20;
      cout << maze[row][col] << "\t";
    }
    cout << endl;
  }
  cout << endl;

  Graph g(maze, mazeRows, mazeCols);

  for (int test = 0; test < 10; test++)
  {
    cout << "TEST " << test << endl;
    int startRow = rand() % mazeRows;
    int startCol = rand() % mazeCols;
    int endRow = rand() % mazeRows;
    int endCol = rand() % mazeCols;

    g.SolveMaze(startRow, startCol, endRow, endCol);
  }

  if (maze)
  {
    for (int row = 0; row < mazeRows; row++)
    {
      if (maze[row])
      {
        delete[] maze[row];
      }
    }
    delete[] maze;
    maze = nullptr;
  }

  return 0;
}
