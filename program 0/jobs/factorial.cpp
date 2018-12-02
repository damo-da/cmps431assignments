#include <iostream>
#include <unistd.h>
using namespace std;
const int sleep_time = 100000;

int main() {
  long res = 1;
  for(int i=1; i<=10; i++) {
    res *= i;
    cout << res << endl;
    
    usleep(sleep_time);
  }
  
}