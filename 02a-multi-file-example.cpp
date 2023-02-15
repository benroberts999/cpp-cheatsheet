#include "multi-file-example/functions.hpp"
#include "multi-file-example/other.hpp"
#include <iostream>
// We must 'include' the header files for any other files we use
// Note: NEVER '#include' a .cpp file
// NB: convention: c++ library files included using <>, and user files w/ ""

int main() {

  // Note that these two functions have the same name.
  // This is allowed, because they are in different "namespaces"

  auto a1 = functions::func1(1);
  auto b1 = functions::func2(1);

  auto a2 = other::func1(1);
  auto b2 = other::func2(1);

  std::cout << a1 << " " << b1 << "\n";
  std::cout << a2 << " " << b2 << "\n";
}