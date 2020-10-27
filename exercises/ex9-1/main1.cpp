#include "grade_list.h"
#include <iostream>

/**
 * No TODOs here.  Just an example of how to use GradeList.
 */

using namespace std;

int main(void) {

  GradeList gl;

  gl.add(20.0); gl.add(30.0); gl.add(40.0);
  gl.add(15.0); gl.add(15.0); gl.add(75.0);
  gl.add(85.0); gl.add(40.0); gl.add(42.0);

  cout << "80th percentile was: " << gl.percentile(80.0) << endl;
  return 0;
}
