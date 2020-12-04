#include <stdexcept>
#include "bounded_stack.h"

void BoundedStack::push(double x) {
  if (size == cap)
     throw std::overflow_error("bounded stack is full");
  Stack::push(x);
}
