#include <stdio.h>
#include "functions.h"
// include the header files again
#include <stdio.h>
#include "functions.h"

int main() {
  float a = 5, b = 8;
  printf("%f divided by %f is %f\n", a, b, div(a, b));

  // To test mul
  //printf("%f x %f is %f (expected 40)\n", a, b, mul(a, b));

  // to test fac
  //printf("factorial of -4 is %d (expected 0)\n", fac(-4));
  //printf("factorial of 10 is %d (expected 3628800)\n", fac(10));

  return 0;
}
