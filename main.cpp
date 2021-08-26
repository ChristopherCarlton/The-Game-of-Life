#include "Grid.h"
#include "Mode.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(){
  Mode mo;
  string modeType;
  string input;
  int rows;
  int cols;
  float density;
  cout << "The Game of Life!" << endl;
  cout << "Enter 1 if you wish to provide a map file of the world in which the simulation will be carried out." << endl;
  cout << "Enter 2 if you want to use random assignmemt." << endl;
  cin >> input;
  //opens a file to where the simulation will be carried out
  if(input == "1"){
    ofstream file;
    string fileName;
    cout << "Enter the file name: " << endl;
    cin >> fileName;
    file.open(fileName);
    cout << "What are the dimensions for the world?" << endl;
    cout << "Enter the number of rows: " << endl;
    cin >> rows;
    cout << "Enter the number of colomns: " << endl;
    cin >> cols;
    cout << "Enter a decimal value (greater than 0 and less than or equal to 1) representing the initial population density of the world for the first generation: " << endl;
    cin >> density;
    cout << "Modes: Classic, Doughnut, Mirror" << endl;
    cout << "Enter the mode you wish to run: " << endl;
    cin >> modeType;
    //uploads simulation to file given input
    if(modeType == "Classic"){
      file << rows << '\n' << cols << '\n' << mo.runClassic(rows, cols, density);
      file.close();
      cout << "The Game of Life complete!" << endl;
    }
    else if(modeType == "Doughnut"){
      file << rows << '\n' << cols << '\n' << mo.runDoughnut(rows, cols, density);
      file.close();
      cout << "The Game of Life complete!" << endl;
    }
    else if(modeType == "Mirror"){
      file << rows << '\n' << cols << '\n' << mo.runMirror(rows, cols, density);
      file.close();
      cout << "The Game of Life complete!" << endl;
    }
    else{
      cout << "Try again check inputs." << endl;
    }
  }
  //runs program on command line given options to see each generation at a single time or all at once
  else if(input == "2"){
    cout << "What are the dimensions for the world?" << endl;
    cout << "Enter the number of rows: " << endl;
    cin >> rows;
    cout << "Enter the number of colomns: " << endl;
    cin >> cols;
    cout << "Enter a decimal value (greater than 0 and less than or equal to 1) representing the initial population density of the world for the first generation: " << endl;
    cin >> density;
    cout << "Modes: Classic, Doughnut, Mirror" << endl;
    cout << "Enter the mode you wish to run: " << endl;
    cin >> modeType;
    string ans;
    if(modeType == "Classic"){
      string classic = mo.runClassic(rows, cols, density);
      cout << "Would you like a pause in between generations? (yes,no)";
      cin >> ans;
      if(ans == "yes"){
        for(int i = 0; i < classic.size(); i++){
          if(classic[i] == 'G'){
            string nothing = "";
            cout << "Enter any letter for next generation: (to end enter exit)" << endl;
            cin >> nothing;
            if(nothing == "exit"){
              break;
            }
          }
          cout << classic[i];
        }
      }
      if(ans == "no"){
        cout << mo.runClassic(rows, cols, density) << endl;
      }
    }
    else if(modeType == "Doughnut"){
      string doughnut = mo.runDoughnut(rows, cols, density);
      cout << "Would you like a pause in between generations? (yes,no)";
      cin >> ans;
      if(ans == "yes"){
        for(int i = 0; i < doughnut.size(); i++){
          if(doughnut[i] == 'G'){
            string nothing = "";
            cout << "Enter any letter for next generation: (to end enter exit)" << endl;
            cin >> nothing;
            if(nothing == "exit"){
              break;
            }
          }
          cout << doughnut[i];
        }
        cout << "The Game of Life complete!" << endl;
      }
      if(ans == "no"){
        cout << mo.runDoughnut(rows, cols, density) << endl;
        cout << "The Game of Life complete!" << endl;
      }
    }
    else if(modeType == "Mirror"){
      string mirror = mo.runMirror(rows, cols, density);
      cout << "Would you like a pause in between generations? (yes,no)";
      cin >> ans;
      if(ans == "yes"){
        for(int i = 0; i < mirror.size(); i++){
          if(mirror[i] == 'G'){
            string nothing = "";
            cout << "Enter any letter for next generation: (to end enter exit)" << endl;
            cin >> nothing;
            if(nothing == "exit"){
              break;
            }
          }
          cout << mirror[i];
        }
        cout << "The Game of Life complete!" << endl;
      }
      if(ans == "no"){
        cout << mo.runMirror(rows, cols, density) << endl;
        cout << "The Game of Life complete!" << endl;
      }
    }
    else{
      cout << "Try again check inputs." << endl;
    }
  }
  else{
    cout << "Try again check inputs." << endl;
  }
  return 0;
}
