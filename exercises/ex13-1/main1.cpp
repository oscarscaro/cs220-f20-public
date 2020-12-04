#include <iostream>
#include <string>
#include "stack.h"
#include "bounded_stack.h"

/***** PART 5 - add exception handling ****/

int main() {

  Stack ustack;
  BoundedStack bstack(15);  // change to 5 after adding error handling in PART 5

  // test isEmpty
  std::cout << "Stacks should start out empty..." << std::endl;
  std::cout << "ustack isEmpty(): ";
  if (ustack.isEmpty())
    std::cout << "true";
  else
    std::cout << "false";
  std::cout << std::endl;
  std::cout << "bstack isEmpty(): ";
  if (bstack.isEmpty())
    std::cout << "true";
  else
    std::cout << "false";
  std::cout << std::endl;
  
  // add ten values into the stacks
  for (double d = 0 ; d < 25 ; d += 2.5 ) {
    ustack.push(d);
    bstack.push(d);
  }

  // test isEmpty
  std::cout << "Stacks both should contain items now..." << std::endl;
  std::cout << "ustack isEmpty(): ";
  if (ustack.isEmpty())
    std::cout << "true";
  else
    std::cout << "false";
  std::cout << std::endl;
  std::cout << "bstack isEmpty(): ";
  if (bstack.isEmpty())
    std::cout << "true";
  else
    std::cout << "false";
  std::cout << std::endl;

  // test top
  std::cout << "Top value on ustack is now: " << ustack.top() << std::endl;
  std::cout << "And calling it again should give same: " << ustack.top() << std::endl;
  std::cout << "Top value on bstack is now: " << bstack.top() << std::endl;
  std::cout << "And calling it again should give same: " << bstack.top() << std::endl;

  // print the stacks
  std::cout << ustack << std::endl;
  std::cout << bstack << std::endl;

  // remove eight elements from the stack
  for (int i = 0; i < 8 ; i++) {
      ustack.pop();
      bstack.pop();
  }

  // test top again
  std::cout << "Top value on ustack is now: " << ustack.top() << std::endl;
  std::cout << "And calling it again should give same: " << ustack.top() << std::endl;
  std::cout << "Top value on bstack is now: " << bstack.top() << std::endl;
  std::cout << "And calling it again should give same: " << bstack.top() << std::endl;

  // print the stacks
  std::cout << ustack << std::endl;
  std::cout << bstack << std::endl;

  // once exception handling has been implemented, it would be a good idea
  // to add code to pop until stack is empty and then call pop, top, isEmpty here


  // enter a bunch of values from standard input
  std::cout << "enter values to push, ^d to exit" << std::endl;
  std::cin >> ustack;

  // print the resulting stack
  std::cout << ustack << std::endl;

  return 0;
}
