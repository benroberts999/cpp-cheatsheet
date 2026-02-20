#include "some_functions.hpp"
#include "header-only-library.hpp"

namespace my_functions {

int func1(int input) {
  int output = input * 3;
  return output;
}

int func2(int input) {
  // from header-only-library:
  int output = add(input, 3);
  return output;
}

} // namespace my_functions