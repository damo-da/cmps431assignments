#ifndef SCHEDULER_H
#define SCHEDULER_H

#define JOBS_MAX 100

#include <iostream>
#include <queue>

void openFile(std::ifstream&, char*);
void readJobs(std::ifstream&);
void run(int);

class Job {
public:
  Job(int pid, int arrival, int burst, int priority):
        pid(pid), 
        arrival(arrival),
        burst(burst),
        priority(priority)
  {
  }
  
  void print();

  int pid, arrival, burst, priority;
};

class JOBS {
public:
  static std::queue<Job*> New;
  static std::queue<Job*> Ready;
  static std::queue<Job*> Running;
  static std::queue<Job*> Terminated;
  static std::queue<Job*> Blocked;
  
  static std::vector<Job*> File_Jobs;
  
  static void print();
  static void printFileJobs();
  
};


#endif //SCHEDULER_H