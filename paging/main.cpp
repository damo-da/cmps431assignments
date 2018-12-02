#include "header.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
  if(argc != 3) {
    cout << "Please enter two arguments (filename and mode=1/2/3)" << endl;
    return 1;
  }
  int mode = argv[2][0] - '0';
  
  if(mode <= 0 || mode > 3){
    cout << "Mode must be equal to 1, 2, or 3." << endl;
    return 2;
  }
  
  ifstream infile;
  openFile(infile, argv[1]);
  
  auto pagingAddresses = readPagingAddresses(infile);
  
  applyAlgorithm(pagingAddresses, mode);
  infile.close();
  
  return 0;
}

void openFile(ifstream& inFile, char* fileName){
  inFile.open(fileName);

  if(!inFile) {
    cerr << "Error: Could not open " << fileName << endl;
    exit(1);
  }
}

vector<int> readPagingAddresses(ifstream& inFile){
  
  vector<int> ret;
  int address;
  
  while (inFile >> address) {
    ret.push_back(address);
  }
  
  return ret;
}
