#ifndef _BOUNDED_STACK_H
#define _BOUNDED_STACK_H

#include "stack.h"

/* A derived class for bounded stacks. */

class BoundedStack : public Stack {

 public:

 BoundedStack(int capacity) : Stack(capacity) { }

  virtual void push(double x) override;

};

#endif
