#ifndef _STACK_H
#define _STACK_H

#include <iostream>

/* A stack class for real numbers. */

class Stack {


  /****** PART 2 - implement basic functionality *********/
 protected:
  int size;     // The number of elements in the stack
  int cap;      // The current array capacity

 private:
  double* data;    // The storage for elements in the stack 

 public:

  /* The default constructor creates an empty stack with enough
     storage for the parameter capacity, or 1 if not specified.
   */                                                                       
  //TODO: Uncomment the below header and fill in
  //Stack(int capacity) { }

  /* Deallocates all the memory associated with the stack.
   */
  //TODO: Uncomment the below header and fill in
  //virtual ~Stack() { }

 /* Indicates whether or not there are any elements on the stack.
  */
  //TODO: Uncomment the below header and fill in
  //bool isEmpty() const { }

 /* Pops off the most recently entered element of the stack.
    Throw an underflow exception if the stack is empty.
 */
  //TODO: Uncomment the below header and fill in
  //double pop();

 /* Pushes an element onto the top of the stack. 
    Throw an overflow exception if this fails.
  */
  //TODO: Uncomment the below header and fill in
  //virtual void push(double x);

 /* Find out the top value of the stack.
    Throw an underflow exception if the stack is empty.
  */
  //TODO: Uncomment the below header and fill in
  //double top() const;


/********************  this code is provided for you ***************/
 
 class iterator {
 private:
   int cur;
   Stack* mine;
 public:
 iterator(Stack* st, int where = 0) : cur(where), mine(st) { }
   iterator& operator++() { cur++; return *this;}
   bool operator!=(const iterator & o) const { 
     return mine != o.mine || cur != o.cur; 
   }
   double& operator*() const { 
     if (cur == mine->size) 
       throw std::range_error("can't dereference iterator");
     return mine->data[cur];
   }
 };

 iterator begin() { return iterator(this); }
 iterator end() { return iterator(this, size); }

 class const_iterator {
 private:
   int cur;
   const Stack* mine;
 public:
   const_iterator(const Stack* st, int where = 0) : cur(where), mine(st) { }
   const_iterator& operator++() { cur++; return *this;}
   bool operator!=(const const_iterator & o) const { 
     return mine != o.mine || cur != o.cur; 
   }
   const double& operator*() const { 
     if (cur == mine->size) 
       throw std::range_error("can't dereference iterator");
     return mine->data[cur];
   }
 };

 const_iterator cbegin() const { return const_iterator(this); }
 const_iterator cend() const { return const_iterator(this, size); }

};

/****** PART 3 - implement operator<< and operator>> *********/
  //TODO: Uncomment the below header and write in stack.cpp
  //std::ostream& operator<<(std::ostream& os, const Stack& s);

  //TODO: Uncomment the below header and write in stack.cpp
  //std::istream& operator>>(std::istream& is, Stack& s);

#endif // STACK_H
