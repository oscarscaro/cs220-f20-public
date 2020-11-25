#ifndef _STACK_H
#define _STACK_H

#include <iostream>

/* A stack class for real numbers. */

class Stack {

  /****** PART B - implement basic functionality *********/
 protected:
  int size;     // The number of elements in the stack
  int cap;      // The current array capacity

 private:
  double* data;    // The storage for elements in the stack 

 public:

  /* The default constructor creates an empty stack with enough
     storage for the parameter capacity, or 1 if not specified.
   */                                                                       
 Stack(int capacity = 1) : size(0), cap(capacity), data(new double[cap]) { }

  /* Deallocates all the memory associated with the stack.
   */
 virtual ~Stack() { delete[] data; }

 /* Indicates whether or not there are any elements on the stack.
  */
 bool isEmpty() const { return size==0; }

 /* Pops off the most recently entered element of the stack.
    Throw an underflow exception if the stack is empty.
 */
 double pop();

 /* Pushes an element onto the top of the stack. 
    Throw an overflow exception if this fails.
  */
 virtual void push(double x);

 /* Find out the top value of the stack.
    Throw an underflow exception if the stack is empty.
  */
 double top() const;


 /********** PART C - add const_iterator and overloaded I/O operators ********/
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

std::ostream& operator<<(std::ostream& os, const Stack& s);
std::istream& operator>>(std::istream& is, Stack& s);

#endif // STACK_H
