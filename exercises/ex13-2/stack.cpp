#include <stdexcept>
#include <exception>
#include <iostream>
#include "stack.h"

using std::istream;  using std::ostream;

double Stack::pop() {
  if (isEmpty())
    throw std::underflow_error("can't pop an empty stack");
  double val = top();
  size--;
  return val;
}

double Stack::top() const {
  if (isEmpty())
    throw std::underflow_error("can't get top from empty stack");
  return data[size-1]; 
}

void Stack::push(double d) {
  if (size == cap) {
    cap *= 2;
    double* temp;
    try {
      temp = new double[cap];
    } catch (std::bad_alloc ba) {
      throw std::overflow_error("can't grow stack any more");
    }
    for (int i = 0; i < size; i++)
      temp[i] = data[i];
    delete [] data;
    data = temp;
  }
  data[size++] = d;
}

std::ostream& operator<<(std::ostream& os, const Stack& s) {
  bool first = true;
  os << "[";
  for (Stack::const_iterator it = s.cbegin(); it != s.cend(); ++it) {
    if (first) {
      first = false;
    }
    else 
      os << " ";
    os << *it;
  }
  os << "]" << std::flush;
  return os;
}

std::istream& operator>>(std::istream& is, Stack& s) {
  double d;
  bool full = false;
  while (is >> d && !full) {
    try {
      s.push(d);
    }
    catch (std::overflow_error e) {
      full = true;
    }
  }
  return is;
}
