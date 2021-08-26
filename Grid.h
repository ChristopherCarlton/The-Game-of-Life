#ifndef GRID_H
#define GRID_H

#include <string>
using namespace std;

class Grid{
public:
  Grid();
  Grid(int rowDimensions, int colDimensions);
  ~Grid();
  int neighbors(int i, int j);
  int doughnutNeighbors(int i, int j);
  int mirrorNeighbors(int i, int j);
  void populate(float density);
  char getGridPosition(int iIndex, int jIndex);
  void setPos(int i, int j, char c);
  bool emptyGrid();
  std::string print();



private:
  char **mygrid;
  int rowLength;
  int colLength;
  int size;
};

#endif
