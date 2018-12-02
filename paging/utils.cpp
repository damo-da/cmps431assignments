#include "header.hpp"

using namespace std;

void printFrameTable(Memory& mem, bool pf=false){
  cout << "Frame " ;
  
  for(auto const& val:mem) {
    if (val == -1)
      cout << "#";
    else
      cout << val;
    cout << " ";
  }
  
  if (pf) {
    cout << ">>> Page fault";
  }
  cout << endl;
}

Memory initRAM() {
  Memory ret;
  for(int i=0; i<FRAME_SIZE; i++){
    ret[i] = -1;
  }
  return ret;
}