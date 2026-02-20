#include "some_functions.hpp"
#include <iostream>
// We must 'include' the header files for any other files we use
// Note: NEVER '#include' a .cpp file
// NB: convention: c++ library files included using <>, and user files w/ ""

int main() {

  // Note that these two functions have the same name.
  // This is allowed, because they are in different "namespaces"

  auto a1 = my_functions::func1(1);
  auto b1 = my_functions::func2(1);

  std::cout << a1 << " " << b1 << "\n";
}