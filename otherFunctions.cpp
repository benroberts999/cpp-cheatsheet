#include "otherFunctions.hpp"
#include <iostream>

namespace OtherFunctions {

double multiply(double x1, double x2) {
  std::cout << "Calling the OtherFunctions version of multiply: " << x1 << " * "
            << x2 << " = \n";
  return x1 * x2;
}

} // namespace OtherFunctions
