#include "Mode.h"
#include "Grid.h"
#include <iostream>
using namespace std;

Mode::Mode(){
  Grid *firstGeneration = new Grid;
  Grid *secondGeneration = new Grid;
  Grid *thirdGeneration = new Grid;
  script = "";
}

Mode::~Mode(){
}

//Starts off the simulation by computing the first three generations
string Mode::runClassic(int rows, int cols, float density){
  int generation = 1;
  Grid *firstGeneration = new Grid(rows, cols);
  Grid *secondGeneration = new Grid(rows, cols);
  Grid *thirdGeneration = new Grid(rows, cols);
  firstGeneration->populate(density);
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += firstGeneration->print();
  generation++;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      //number of neighbors is spot
      //I understand I could have created a method for this because I call all
      //these steps 5 times to be more efficient, but I had trouble passing in
      //Grid* references
      int spot = firstGeneration->neighbors(i,j);
      if(spot <= 1.5){
        secondGeneration->setPos(i,j, '-');
      }
      if(spot >= 1.5 && spot <= 2.5){
        secondGeneration->setPos(i,j, firstGeneration->getGridPosition(i,j));
      }
      if(spot >= 2.51 && spot <= 3.5){
        secondGeneration->setPos(i,j, 'X');
      }
      if(spot >= 3.51){
        secondGeneration->setPos(i,j, '-');
      }
    }
  }
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += secondGeneration->print();
  generation++;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      //number of neighbors is spot
      float spot = (secondGeneration->neighbors(i,j) + firstGeneration->neighbors(i,j))/2;
      if(spot <= 1.5){
        thirdGeneration->setPos(i,j, '-');
      }
      if(spot >= 1.5 && spot <= 2.5){
        thirdGeneration->setPos(i,j, secondGeneration->getGridPosition(i,j));
      }
      if(spot >= 2.51 && spot <= 3.5){
        thirdGeneration->setPos(i,j, 'X');
      }
      if(spot >= 3.51){
        thirdGeneration->setPos(i,j, '-');
      }
    }
  }
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += thirdGeneration->print();
  generation++;

  //after the first three generations are populated, then I create a turn concept
  //to cycle through n generations yet only changing references of my three generations
  //pointers
  int turn = 1;
  while(true){
    if(turn == 1){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->neighbors(i,j) + secondGeneration->neighbors(i,j) + thirdGeneration->neighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            firstGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            firstGeneration->setPos(i,j, thirdGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            firstGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            firstGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += firstGeneration->print();
      generation++;
      turn++;
      if(firstGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }

    if(turn == 2){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->neighbors(i,j) + secondGeneration->neighbors(i,j) + thirdGeneration->neighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            secondGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            secondGeneration->setPos(i,j, firstGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            secondGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            secondGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += secondGeneration->print();
      generation++;
      turn++;
      if(secondGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }

    if(turn == 3){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->neighbors(i,j) + secondGeneration->neighbors(i,j) + thirdGeneration->neighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            thirdGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            thirdGeneration->setPos(i,j, secondGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            thirdGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            thirdGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += thirdGeneration->print();
      generation++;
      turn = 1;
      if(thirdGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }
  }
  return script;
}

string Mode::runDoughnut(int rows, int cols, float density){
  int generation = 1;
  Grid *firstGeneration = new Grid(rows, cols);
  Grid *secondGeneration = new Grid(rows, cols);
  Grid *thirdGeneration = new Grid(rows, cols);
  firstGeneration->populate(density);
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += firstGeneration->print();
  generation++;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int spot = firstGeneration->doughnutNeighbors(i,j);
      if(spot <= 1.5){
        secondGeneration->setPos(i,j, '-');
      }
      if(spot >= 1.5 && spot <= 2.5){
        secondGeneration->setPos(i,j, firstGeneration->getGridPosition(i,j));
      }
      if(spot >= 2.51 && spot <= 3.5){
        secondGeneration->setPos(i,j, 'X');
      }
      if(spot >= 3.51){
        secondGeneration->setPos(i,j, '-');
      }
    }
  }
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += secondGeneration->print();
  generation++;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int spot = secondGeneration->doughnutNeighbors(i,j) + firstGeneration->doughnutNeighbors(i,j);
      spot /= 2;
      if(spot <= 1.5){
        thirdGeneration->setPos(i,j, '-');
      }
      if(spot >= 1.5 && spot <= 2.5){
        thirdGeneration->setPos(i,j, secondGeneration->getGridPosition(i,j));
      }
      if(spot >= 2.51 && spot <= 3.5){
        thirdGeneration->setPos(i,j, 'X');
      }
      if(spot >= 3.51){
        thirdGeneration->setPos(i,j, '-');
      }
    }
  }
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += thirdGeneration->print();
  generation++;

  int turn = 1;
  while(true){
    if(turn == 1){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->doughnutNeighbors(i,j) + secondGeneration->doughnutNeighbors(i,j) + thirdGeneration->doughnutNeighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            firstGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            firstGeneration->setPos(i,j, thirdGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            firstGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            firstGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += firstGeneration->print();
      generation++;
      turn++;
      if(firstGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }

    if(turn == 2){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->doughnutNeighbors(i,j) + secondGeneration->doughnutNeighbors(i,j) + thirdGeneration->doughnutNeighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            secondGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            secondGeneration->setPos(i,j, firstGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            secondGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            secondGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += secondGeneration->print();
      generation++;
      turn++;
      if(secondGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }

    if(turn == 3){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->doughnutNeighbors(i,j) + secondGeneration->doughnutNeighbors(i,j) + thirdGeneration->doughnutNeighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            thirdGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            thirdGeneration->setPos(i,j, secondGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            thirdGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            thirdGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += thirdGeneration->print();
      generation++;
      turn = 1;
      if(thirdGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }
  }
  return script;
}

string Mode::runMirror(int rows, int cols, float density){
  int generation = 1;
  Grid *firstGeneration = new Grid(rows, cols);
  Grid *secondGeneration = new Grid(rows, cols);
  Grid *thirdGeneration = new Grid(rows, cols);
  firstGeneration->populate(density);
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += firstGeneration->print();
  generation++;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int spot = firstGeneration->mirrorNeighbors(i,j);
      if(spot <= 1.5){
        secondGeneration->setPos(i,j, '-');
      }
      if(spot >= 1.5 && spot <= 2.5){
        secondGeneration->setPos(i,j, firstGeneration->getGridPosition(i,j));
      }
      if(spot >= 2.51 && spot <= 3.5){
        secondGeneration->setPos(i,j, 'X');
      }
      if(spot >= 3.51){
        secondGeneration->setPos(i,j, '-');
      }
    }
  }
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += secondGeneration->print();
  generation++;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      int spot = secondGeneration->mirrorNeighbors(i,j) + firstGeneration->mirrorNeighbors(i,j);
      spot /= 2;
      if(spot <= 1.5){
        thirdGeneration->setPos(i,j, '-');
      }
      if(spot >= 1.5 && spot <= 2.5){
        thirdGeneration->setPos(i,j, secondGeneration->getGridPosition(i,j));
      }
      if(spot >= 2.51 && spot <= 3.5){
        thirdGeneration->setPos(i,j, 'X');
      }
      if(spot >= 3.51){
        thirdGeneration->setPos(i,j, '-');
      }
    }
  }
  script += "Generation " + to_string(generation) + ":" + "\n";
  script += thirdGeneration->print();
  generation++;

  int turn = 1;
  while(true){
    if(turn == 1){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->mirrorNeighbors(i,j) + secondGeneration->mirrorNeighbors(i,j) + thirdGeneration->mirrorNeighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            firstGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            firstGeneration->setPos(i,j, thirdGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            firstGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            firstGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += firstGeneration->print();
      generation++;
      turn++;
      if(firstGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }

    if(turn == 2){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->mirrorNeighbors(i,j) + secondGeneration->mirrorNeighbors(i,j) + thirdGeneration->mirrorNeighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            secondGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            secondGeneration->setPos(i,j, firstGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            secondGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            secondGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += secondGeneration->print();
      generation++;
      turn++;
      if(secondGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }

    if(turn == 3){
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
          int spotNeighbors = firstGeneration->mirrorNeighbors(i,j) + secondGeneration->mirrorNeighbors(i,j) + thirdGeneration->mirrorNeighbors(i,j);
          float avg = spotNeighbors / 3;
          if(avg <= 1.5){
            thirdGeneration->setPos(i,j, '-');
          }
          if(avg >= 1.5 && avg <= 2.5){
            thirdGeneration->setPos(i,j, secondGeneration->getGridPosition(i,j));
          }
          if(avg >= 2.51 && avg <= 3.5){
            thirdGeneration->setPos(i,j, 'X');
          }
          if(avg >= 3.51){
            thirdGeneration->setPos(i,j, '-');
          }
        }
      }
      script += "Generation " + to_string(generation) + ":" + "\n";
      script += thirdGeneration->print();
      generation++;
      turn = 1;
      if(thirdGeneration->emptyGrid() == 1 || generation == 10000){
        break;
      }
    }
  }
  return script;
}
