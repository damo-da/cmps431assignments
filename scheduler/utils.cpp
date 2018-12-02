#include "header.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

void printQueue(queue<Job*> jobQueue, string title){
  
  queue<Job*> q = jobQueue;
  Job* elem = nullptr;
  
  cout << title << ":: ";
  
  if(q.empty()){
    cout << "empty."<< endl; return;
  }
  cout << endl;
  
  // cout << "S.N.\tPID\tArrival\tBurst\tPriority" << endl;
  int i=0;
  while (!q.empty())
  {
      elem = q.front();
      // std::cout << ++i << ".\t" << elem->pid << "\t" << elem->arrival << "\t" << 
            // elem->burst << "\t" << elem->priority <<"\n";
      elem->print();
      q.pop();
  } 
  // cout << endl;
}

void JOBS::printFileJobs() {
  cout << "All jobs: " << endl;
  for (auto &x: JOBS::File_Jobs) {
    x->print();
  }
}
void JOBS::print(){
  int total = JOBS::New.size() + JOBS::Ready.size() + JOBS::Running.size() + JOBS::Terminated.size() + JOBS::Blocked.size();
  cout << total << " total jobs" << endl;
  
  printQueue(JOBS::New, "New");
  printQueue(JOBS::Ready, "Ready");
  printQueue(JOBS::Running, "Running");
  printQueue(JOBS::Terminated, "Terminated");
  printQueue(JOBS::Blocked, "Blocked");
}

void Job::print() {
  std::cout << "Job: <pid=" << this->pid<< ", ";
  
  if(this->arrival >= 0) 
    std::cout << "arrival: " << this->arrival << ", ";
  
  if(this->burst > 0)
    std::cout<< "burst: " << this->burst << ", ";
  
  cout << "priority: " << this->priority << ">" << endl;
}

std::queue<Job*> JOBS::New;
std::queue<Job*> JOBS::Ready;
std::queue<Job*> JOBS::Running;
std::queue<Job*> JOBS::Terminated;
std::queue<Job*> JOBS::Blocked;

std::vector<Job*> JOBS::File_Jobs;
