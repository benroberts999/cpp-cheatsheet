#include <iostream>

// If we want to use a function, it must be *declared* before we use it.
// We can do this either by definig the entire function at the start of the
// file, (like the `multiply`) example, or by just *declaring* it at the start,
// then we may define it anywhere (like the `print value`) example.
// You can decare functions in different files, using another .cpp and header
// file = see multi-file-example

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

// The following are declarations. These functions are implemented/defined at
// the bottom of the file

// pass by value (copy)
void printValue(int x1);

// pass by reference
void modifyValue(int &x1);

// pass by const reference
void dontModify(const int &x1);

int main() {
  //****************************************************************************
  // Use some functions, basic template, and namespaces:
  // These functions are defined in the files: src/functions,
  // src/otherFunctions, src/templates.
  // See those files for explanation of namespace, overload
  std::cout << "\nFunctions, namespaces, templates:\n";

  double d1 = 1.5;
  double d2 = 2.5;
  auto res1 = multiply(d1, d2);
  std::cout << res1 << "\n";

  // "function overloading"
  int i1 = 1;
  int i2 = 2;
  auto res2 = multiply(i1, i2);
  std::cout << res2 << "\n";

  // pass by value (copy) - this is the default
  int my_2nd_int = 6;
  std::cout << "Before: " << my_2nd_int << "\n";
  printValue(my_2nd_int);
  std::cout << "After: " << my_2nd_int << "\n";

  // pass by reference
  std::cout << "Before: " << my_2nd_int << "\n";
  modifyValue(my_2nd_int);
  std::cout << "After: " << my_2nd_int << "\n";

  // pass by const reference
  std::cout << "Before: " << my_2nd_int << "\n";
  dontModify(my_2nd_int);
  std::cout << "After: " << my_2nd_int << "\n";

  //****************************************************************************
  std::cout << "\nLambda functions:\n";
  // Lambdas are "unnamed" function objects, defined inline
  // They are often passed to other functions (like standard algorithms)

  // [captures](parameters){function body;}
  // Captures means local variables are "captured" in scope.
  // Probably, captures are rarely needed, in which case the [] are empty

  auto my_lambda = [](double x) { return x * 2.0; };

  double a = 3.0;
  auto my_lambda2 = [a](double x) { return x * a; };

  std::cout << my_lambda(3.0) << "\n";
  std::cout << my_lambda2(3.0) << "\n";
}

//------------------------------------------------------------------------------
/// Function defintions:

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