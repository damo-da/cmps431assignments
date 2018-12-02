#include <iostream>
#include <unistd.h>
using namespace std;
const int sleep_time = 100000;

int main() {
  for(int i=0; i<100; i++) {
    cout << '#' << flush;
    
    usleep(sleep_time);
  }
  cout << endl;
  
}