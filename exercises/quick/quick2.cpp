#include <iostream>
#include <vector>

using std::cout; 
using std::endl; 
using std::vector;

void sum(/* TODO: complete this part */) {
  // TODO: complete the function to calculate the sum
  // of all v's values. Make use of references.
  
}

int main() {
  vector<int> v;
  for (int i = 0; i < 87; i = i + 2) {
      v.push_back(i);
  }
  int result = 0;
  sum (v, result);
  cout << "sum of all v's elements is: " << result << endl;
  
  return 0;
}