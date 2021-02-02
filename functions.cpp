#include "functions.hpp"
#include <iostream>

namespace ExampleFunctions {

double multiply(double x1, double x2) {
  std::cout << "Calling the double version of multiply function: " << x1
            << " * " << x2 << " = \n";

  const double result = x1 * x2;
  // of course, you can do this on a single line...but a function body may be as
  // long or short as you like. It's best to try to keep them short, so they are
  // easier to understand
  return result;
}

// function overloading:
int multiply(int x1, int x2) {
  std::cout << "Calling the integer version of multiply function: " << x1
            << " * " << x2 << " = \n";
  return x1 * x2;
}

// pass by value (copy)
void printValue(int x1) {
  std::cout << "printValue: " << x1 << "\n";
  x1 *= 6; // modify our copy of x1 - outside is not affected
  std::cout << "printValue: " << x1 << "\n";
}

// pass by reference
void modifyValue(int &x1) {
  std::cout << "modifyValue\n";
  // modify our *reference* to x1 - outside *is* affected
  x1 = x1 * 2;
}

// pass by const reference
void dontModify(const int &x1) {
  std::cout << "dontModify " << x1 << "\n";
  // x1 = x1 * 2; // this is not allowed, since in this scope, x1 is const
}

} // namespace ExampleFunctions
