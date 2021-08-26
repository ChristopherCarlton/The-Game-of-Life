#ifndef MODE_H
#define MODE_H

#include <string>
#include "Grid.h"
using namespace std;

class Mode{
public:
  Mode();
  ~Mode();
  std::string runClassic(int rows, int cols, float dens);
  std::string runDoughnut(int rows, int cols, float dens);
  std::string runMirror(int rows, int cols, float dens);
private:
  Grid *firstGeneration;
  Grid *secondGeneration;
  Grid *thirdGeneration;
  string script;
};

#endif
