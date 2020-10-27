#include <iostream>
#include <sstream>
#include <string>

using std::stringstream; 
using std::cout;
using std::cin; 
using std::string; 
using std::endl;

// TODO: Function to find and print all words
// in str with a length greater than k 
void findWords(string str, int K) {
    string word;
    // using stringstream to break the string into tokens
    stringstream ss(str); // create a stringstream with content str
    // TODO: write code to find words in ss with a length greater
    // than k and print them out
    
}

int main() {
    string str = "Here is a bunch of space separated words";
    int k = 3;
    findWords(str, k);
    return 0;
} 