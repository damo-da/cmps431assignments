#include "header.hpp"
using namespace std;

bool alreadyInRAM(Memory& mem, int id){
  return std::find(std::begin(mem), std::end(mem), id) != std::end(mem);
}
int getIndexOf(Memory& mem, int num){
  for(auto i = 0; i<FRAME_SIZE; i++){
    if (mem[i] == num) return i;
  }
  
  return -1;
}