#include <iostream>
#include <vector>
#include <string>
#include "header.hpp"

using namespace std;

int sch_time = 0;
void moveFileJobsToNewQueue(){
  vector<Job*> remainingJobs;
  vector<Job*> jobsToAdd;
  Job* job;
  
  /* Add jobs to the new queue*/
  for (auto jobPtr=JOBS::File_Jobs.begin(); jobPtr<JOBS::File_Jobs.end(); jobPtr++) {
    job = *jobPtr;
    if(job -> arrival <= sch_time) {
      jobsToAdd.push_back(job);
    }else {
      remainingJobs.push_back(job);
    }
    
    // job->arrival--;
  }

  for(auto jobPtr=jobsToAdd.begin(); jobPtr<jobsToAdd.end(); jobPtr++){
    job = *jobPtr;
    
    JOBS::New.push(job);
    JOBS::File_Jobs.erase(std::remove(JOBS::File_Jobs.begin(), JOBS::File_Jobs.end(), job), JOBS::File_Jobs.end());

  }
}

void moveNewJobsToReadyQueue() {
  Job* job;
  while(!JOBS::New.empty()){
    job = JOBS::New.front();
    JOBS::Ready.push(job);
    JOBS::New.pop();
  }
}

int processShortestJob(){
  Job* job;
  Job* shortest=0;
  
  // cout << "Before " << endl;
  // JOBS::print();
  
  // cout << "Shortest is ";
  
  auto copy = JOBS::Ready;
  while(!copy.empty()) {
    job = copy.front();
    copy.pop();
    if (shortest == 0 || shortest->burst > job->burst) {
      shortest = job;
      // cout << "Found shortest job" << endl;
      // shortest->print();
      // job->print();
    }
  }
  
  cout << "Shortest ";
  shortest->print();
  
  queue<Job*> newReadyQueue;
  copy = JOBS::Ready;
  while(!copy.empty()) {
    job = copy.front();
    copy.pop();
    
    if (job == shortest) continue;
    
    newReadyQueue.push(job);
  }
  
  JOBS::Ready = newReadyQueue;
  
  JOBS::Running.push(shortest);
  
  job = JOBS::Running.front();
  
  JOBS::Running.pop();
  
  JOBS::Terminated.push(job);
  
  // cout << "After " << endl;
  // JOBS::print();
  return shortest->burst;
  
}

int processFirstJob(){
  Job* job;
  Job* first = JOBS::Ready.front();
  
  JOBS::Ready.pop();
  
  JOBS::Running.push(first);
  
  job = JOBS::Running.front();
  JOBS::Running.pop();
  
  JOBS::Terminated.push(job);
  
  return first->burst;
}

int processRoundRobin(){
  Job* job;
  
  while (!JOBS::Ready.empty()){
    job = JOBS::Ready.front();
    JOBS::Ready.pop();
    
    JOBS::Running.push(job);
  }
  
  queue<Job*> newList;
  
  int time = 0;
  while(!JOBS::Running.empty()) {
    job = JOBS::Running.front();
    JOBS::Running.pop();
    
    job->burst -= 1;
    time ++;
    
    if (job -> burst == 0) {
      JOBS::Terminated.push(job);
    }else{
      newList.push(job);      
    }
    
  }
  
  JOBS::Running = newList;
  
  // cout << "Returning " << time << endl;
  return time;
}
void run(int algorithm=1) { // 1 = SJF, 2 = FIFO, 3 = round robin
  cout << "Running simulation" << endl;
  string mode = algorithm==1?"Shortest Job First":(algorithm==2?"FIFO":"Round Robin");
  cout << "Mode = " << mode << endl;
  
  int loopCnt = 0;
  while (true) {
    moveFileJobsToNewQueue();
    moveNewJobsToReadyQueue();
    
    // JOBS::print();
    
    if (JOBS::Ready.empty() && JOBS::Running.empty() && JOBS::Blocked.empty()){
      break;
    }
    
    // cout << "Time = " << sch_time << endl;
    
    if(algorithm == 1) {
      sch_time += processShortestJob();
    } else if(algorithm == 2) {
      sch_time += processFirstJob();

    } else if(algorithm == 3) {
      sch_time += processRoundRobin();

    } else {
      cout << "Unknown scheduling algorithm" << endl;
      exit(1);
    }
    
    // if (loopCnt == 2) break;
    loopCnt++;
    
  }
  cout << "Final state: " << endl;
  JOBS::print();
  
  cout << "Total time: " << sch_time << endl;
  
  
  cout << "End simulation" << endl;
}