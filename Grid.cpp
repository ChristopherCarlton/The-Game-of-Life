#include "Grid.h"
#include <iostream>
using namespace std;

Grid::Grid(){
  rowLength = 0;
  colLength = 0;
  size = 0;
  mygrid = new char*[rowLength];
  for(int j = 0; j < rowLength; ++j){ //memory allocation
    mygrid[j] = new char[colLength];
  }
}

Grid::Grid(int rowDimensions, int colDimensions){
  mygrid = new char*[rowDimensions];
  for(int j = 0; j < rowDimensions; ++j){ //memory allocation
    mygrid[j] = new char[colDimensions];
  }
  rowLength = rowDimensions;
  colLength = colDimensions;
  size = rowDimensions * colDimensions;
}

Grid::~Grid(){
  for(int j = 0; j < rowLength; ++j){
    delete[] mygrid[j];
  }
  delete[] mygrid;
}

void Grid::populate(float density){
  float dens = (density * 100);
  for(int i = 0; i < rowLength; i++){
    for(int j = 0; j < colLength; j++){
      int chance = rand() % 100;
      if(chance <= dens){
        mygrid[i][j] = 'X';
      }
      else{
        mygrid[i][j] = '-';
      }
    }
  }
}

char Grid::getGridPosition(int i, int j){
  return mygrid[i][j];
}

void Grid::setPos(int i, int j, char value){
  mygrid[i][j] = value;
}

bool Grid::emptyGrid(){
  int count = 0;
  bool result;
  for(int i = 0; i < rowLength; i++){
    for(int j = 0; j < colLength; j++){
      if(mygrid[i][j] == 'X'){
        result = false;
      }
      else{
        count++;
      }
    }
  }
  if(count == size){
    result = true;
  }
  return result;
}

int Grid::neighbors(int rowIndex, int colIndex){
  int neighbors = 0;

  //top of cell
  if(rowIndex != 0){
    if(mygrid[rowIndex-1][colIndex] == 'X'){
      neighbors += 1;
    }
  }

  //bottom of cell
  if(rowIndex != rowLength-1){
    if(mygrid[rowIndex+1][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //left of cell
  if(colIndex != 0){
    if(mygrid[rowIndex][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }
  //right of cell
  if(colIndex != colLength-1){
    if(mygrid[rowIndex][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }

  //top right
  if(colIndex != colLength-1 && rowIndex != 0){
    if(mygrid[rowIndex-1][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }

  //top left
  if(rowIndex != 0 && colIndex != 0){
    if(mygrid[rowIndex-1][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }

  //bottom left
  if(rowIndex != rowLength-1 && colIndex != 0){
    if(mygrid[rowIndex+1][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }

  //bottom right
  if(rowIndex != rowLength-1 && colIndex != colLength-1){
    if(mygrid[rowIndex+1][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }
  return neighbors;
}

int Grid::doughnutNeighbors(int rowIndex, int colIndex){
  //get all normal cell locations that aren't off grid
  int neighbors = this->neighbors(rowIndex, colIndex);
  //top of cell and grid but bottom of grid
  if(rowIndex == 0){
    if(mygrid[rowLength-1][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //bottom of cell and grid but top of grid
  if(rowIndex == rowLength-1){
    if(mygrid[0][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //left of cell and grid but right side of grid
  if(colIndex == 0){
    if(mygrid[rowIndex][colLength-1] == 'X'){
      neighbors += 1;
    }
  }
  //right of cell and grid but left side of grid
  if(colIndex == colLength-1){
    if(mygrid[rowIndex][0] == 'X'){
      neighbors += 1;
    }
  }
  //top right of cell but bottom right of grid
  if(colIndex != colLength-1 && rowIndex == 0){
    if(mygrid[rowLength-1][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }
  //top right corner of cell and grid but bottom right corner of cell
  if(colIndex == colLength-1 && rowIndex == 0){
    if(mygrid[rowLength-1][0] == 'X'){
      neighbors += 1;
    }
  }
  //top left of cell but bottom left of grid
  if(rowIndex == 0 && colIndex != 0){
    if(mygrid[rowLength-1][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }
  //top left corner of cell and grid but bottom right corner of cell
  if(rowIndex == 0 && colIndex == 0){
    if(mygrid[rowLength-1][colLength-1] == 'X'){
      neighbors += 1;
    }
  }
  //bottom left of cell but top right of grid
  if(rowIndex == rowLength-1 && colIndex != 0){
    if(mygrid[0][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }
  //bottom left corner of cell and grid but top right corner of cell
  if(rowIndex == rowLength-1 && colIndex == 0){
    if(mygrid[0][colLength-1] == 'X'){
      neighbors += 1;
    }
  }
  //bottom right of cell but top right of grid
  if(rowIndex == rowLength-1 && colIndex != colLength-1){
    if(mygrid[0][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }
  //bottom right corner of cell and grid but top left corner of grid
  if(rowIndex == rowLength-1 && colIndex == colLength-1){
    if(mygrid[0][0] == 'X'){
      neighbors += 1;
    }
  }
  //right side of grid: top right of cell but left side of grid up one
  if(colIndex == colLength-1 && rowIndex != 0){
    if(mygrid[rowIndex-1][0] == 'X'){
      neighbors += 1;
    }
  }
  //right side of grid: bottom right of cell but left of grid down one
  if(colIndex == colLength-1 && rowIndex != rowLength-1){
    if(mygrid[rowIndex+1][0] == 'X'){
      neighbors += 1;
    }
  }
  //left side of grid: top left of cell but right side of grid up one
  if(colIndex == 0 && rowIndex != 0){
    if(mygrid[rowIndex-1][colLength-1] == 'X'){
      neighbors += 1;
    }
  }
  //left side of grid: bottom left of cell but right side of grid down one
  if(colIndex == 0 && rowIndex != rowLength-1){
    if(mygrid[rowIndex+1][colLength-1] == 'X'){
      neighbors += 1;
    }
  }
  return neighbors;
}

int Grid::mirrorNeighbors(int rowIndex, int colIndex){
  //get all normal cell locations that aren't off grid
  int neighbors = this->neighbors(rowIndex, colIndex);
  //top of cell and grid but reflection of itself
  if(rowIndex == 0){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //bottom of cell and grid but reflection of itself
  if(rowIndex == rowLength-1){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //left of cell and grid but reflection of itself
  if(colIndex == 0){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //right of cell and grid but reflection of itself
  if(colIndex == colLength-1){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //top right reflection of cell but right of cell
  if(colIndex != colLength-1 && rowIndex == 0){
    if(mygrid[rowIndex][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }
  //top right corner of cell but reflection of itself
  if(colIndex == colLength-1 && rowIndex == 0){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //top left reflection of cell but left of cell
  if(rowIndex == 0 && colIndex != 0){
    if(mygrid[rowIndex][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }
  //top left corner of cell but reflection of itself
  if(rowIndex == 0 && colIndex == 0){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //bottom left reflection of cell but left of cell
  if(rowIndex == rowLength-1 && colIndex != 0){
    if(mygrid[rowIndex][colIndex-1] == 'X'){
      neighbors += 1;
    }
  }
  //bottom left corner of cell but reflection of itself
  if(rowIndex == rowLength-1 && colIndex == 0){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //bottom right reflection of cell but right of cell
  if(rowIndex == rowLength-1 && colIndex != colLength-1){
    if(mygrid[rowIndex][colIndex+1] == 'X'){
      neighbors += 1;
    }
  }
  //bottom right corner of cell but reflection of itself
  if(rowIndex == rowLength-1 && colIndex == colLength-1){
    if(mygrid[rowIndex][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //right side of grid: top right reflection of cell but top cell
  if(colIndex == colLength-1 && rowIndex != 0){
    if(mygrid[rowIndex-1][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //right side of grid: bottom right reflection of cell but bottom cell
  if(colIndex == colLength-1 && rowIndex != rowLength-1){
    if(mygrid[rowIndex+1][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //left side of grid: top left reflection of cell but top cell
  if(colIndex == 0 && rowIndex != 0){
    if(mygrid[rowIndex-1][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  //left side of grid: bottom left reflection of cell but bottom cell
  if(colIndex == 0 && rowIndex != rowLength-1){
    if(mygrid[rowIndex+1][colIndex] == 'X'){
      neighbors += 1;
    }
  }
  return neighbors;
}


std::string Grid::print(){
  string result = "";
  for(int i = 0; i < rowLength; i++){
    for(int j = 0; j < colLength; j++){
      result += mygrid[i][j];
    }
    result += "\n";
  }
  return result;
}
