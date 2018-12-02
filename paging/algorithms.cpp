#include "header.hpp"
#include <queue>
#include <algorithm>

using namespace std;

bool inVector(std::vector<int>& vec, int val) {
  return std::find(std::begin(vec), std::end(vec), val) != std::end(vec);
}

void removeFromVector(vector<int>& vec, int val) {
  vec.erase(std::remove(vec.begin(), vec.end(), val), vec.end());
}

int getFirstUnmatchingElem(Memory& flock, vector<int>& sheeps) {
  for(auto const& ts:flock){
    if (!inVector(sheeps, ts))return ts;
  }
  return -1;
}

int fifo(std::vector<int> addresses){
  auto memory = initRAM();
  
  int pageFaults = 0;
  bool pf = false;
  queue<int> additions;
  for(auto const& address:addresses){
    printFrameTable(memory, pf);
    pf = false;
    
    int firstBit = address/PAGE_SIZE;
    
    if(alreadyInRAM(memory, firstBit)){
      continue;
    }else{
      int index = getIndexOf(memory, -1);
      
      if (index == -1) {
        pf=true;
        // cout << "Not" << endl;
        auto number = additions.front();
        // cout << "Removing " << number << endl;
        additions.pop();
        pageFaults++;
        // cout << "Removed " << endl;
        int index = getIndexOf(memory, number);
        // cout << "Index is " << index;
        memory[index] = firstBit;
      }else{
        memory[index] = firstBit;
      }
      
      additions.push(firstBit);
    }
  }
  printFrameTable(memory, pf);
  return pageFaults;
}

int lru(std::vector<int> addresses){
  auto memory = initRAM();
  
  int pageFaults = 0;
  
  bool pf=false;
  
  vector<int> additions(FRAME_SIZE);
  for(auto const& address:addresses){
    printFrameTable(memory, pf);
    pf = false;
    
    int firstBit = address/PAGE_SIZE;
    
    if(!alreadyInRAM(memory, firstBit)){
      // cout << "Not already in ram" << endl;
      int index = getIndexOf(memory, -1);
      
      if (index == -1) {
        pf = true;
        pageFaults++;
        
        // cout << "Not" << endl;
        auto number = additions[0];
        
        int index = getIndexOf(memory, number);
        
        // cout << "Removing " << number << endl;
        memory[index] = firstBit;
      }else{
        memory[index] = firstBit;
      }
    }
    
    if(additions.size() < FRAME_SIZE){
      if(inVector(additions, firstBit))
        removeFromVector(additions, firstBit);
      
    }else {
      if(!inVector(additions, firstBit)){
        removeFromVector(additions, additions[0]);
      }else{
        removeFromVector(additions, firstBit);
      }
    }
    additions.push_back(firstBit);
  }
  printFrameTable(memory, pf);
  return pageFaults;
}

int belady(std::vector<int> addresses){
  auto memory = initRAM();
  
  int pageFaults = 0;
  
  bool pf=false;
  
  for(int i=0; i<addresses.size(); i++){
    auto const& address = addresses[i];
    
    printFrameTable(memory, pf);
    pf = false;
    
    int firstBit = address/PAGE_SIZE;
    
    if(!alreadyInRAM(memory, firstBit)){
      // cout << "Not already in ram" << endl;
      int index = getIndexOf(memory, -1);
      
      
      // if(additions.size() < FRAME_SIZE){
      //   if(inVector(additions, firstBit))
      //     removeFromVector(additions, firstBit);
      // 
      // }else {
      //   if(!inVector(additions, firstBit)){
      //     removeFromVector(additions, additions[0]);
      //   }else{
      //     removeFromVector(additions, firstBit);
      //   }
      // }
      // additions.push_back(firstBit);
      // 
      if (index == -1) {
        pf = true;
        pageFaults++;
        
        vector<int> futureRequisite(FRAME_SIZE);
        for(int j=i+1; j<addresses.size(); j++){
          if(!alreadyInRAM(memory, addresses[j]))continue;
          
          if(!inVector(futureRequisite, addresses[j])){
            futureRequisite.push_back(addresses[j]);
          }
          
          if(futureRequisite.size() == FRAME_SIZE-1){
            break;
          }
        }
        
        int swapElem = getFirstUnmatchingElem(memory, futureRequisite);
        index = getIndexOf(memory, swapElem);
        memory[index] = firstBit;
      }else{
        memory[index] = firstBit;
      }
    }
    
    // cout << "For " << address << endl;
    // cout << "BEFORE: " << endl;
    // for (auto i = additions.begin(); i != additions.end(); ++i)
    //   std::cout << *i << ' ';
    // cout<<endl;
    
    
    // cout << "AFTER: " << endl;
    // for (auto i = additions.begin(); i != additions.end(); ++i)
    //   std::cout << *i << ' ';
    // cout<<endl<<endl;
  }
  printFrameTable(memory, pf);
  return pageFaults;
}

void applyAlgorithm(vector<int> addresses, int mode){
  int faults;
  switch (mode) {
    case 1:{
      cout << "Applying FIFO " << endl;
      faults = fifo(addresses);
      break;
    }
    case 2: {
      cout << "Applying LRU" << endl;
      faults = lru(addresses);
      break;
    }
    case 3: {
      cout << "Applying Belady's algorithm" << endl;
      faults = belady(addresses);
      break;
    }
    default: {
      cout << "Unknown algorithm" << endl;
      exit(1);
      
    }
  }
  
  cout << "No. of page faults: " << faults << endl;
}