#include <iostream>
#include <unistd.h>
using namespace std;
const int sleep_time = 100000;

int main() {
  int sum = 0;
  for(int i=1; i<=10; i++) {
    sum += i;
    cout << sum << endl;
    
    usleep(sleep_time);
  }
  
}