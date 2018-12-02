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
  
  ifstream inFile;
  openFile(inFile, argv[1]);
  
  readJobs(inFile);
  
  run(mode);// 1 = SJF, 2 = FIFO, 3 = round robin
  
  inFile.close();
  
  return 0;
}

void openFile(ifstream& inFile, char* fileName){
  inFile.open(fileName);

  if(!inFile) {
    cerr << "Error: Could not open file " << fileName << endl;
    exit(1);
  }
}

void readJobs(ifstream& inFile){
  string headers;
  vector<Job> jobs;
  
  getline(inFile, headers);
  
  int pid, arrival, burst, priority;
  
  while (inFile >> pid >> arrival >> burst >> priority) {
    Job* job = new Job(pid, arrival, burst, priority);
    JOBS::File_Jobs.push_back(job);
  }
}
