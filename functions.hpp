#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
// This is a "header guard" - it stops a header file from ever being included in
// your program more than once. As soon as your program becomes a bit large,
// this is very important.

// A header file defines the functions, but does not implement them

//******************************************************************************
namespace ExampleFunctions {

double multiply(double x1, double x2);

// function overloading: can have different functions with same name if they
// take diferent types are inputs
int multiply(int x1, int x2);

// void function do not have a return value; they typically do something (like a
// subroutine)

// pass by value (copy)
void printValue(int x1);

// pass by reference.
// Note: this avoids needing to make a copy of x1 that is used inside the
// function. When it's just an int/double etc. this is not needed - but when you
// have big data types that are expensive to copy, it is useful
void modifyValue(int &x1);

// pass by const reference. As above, but doesn't allow modification of the
// input variable
void dontModify(const int &x1);

// You can also pass by pointer, const pointer, pointer to const etc

} // namespace ExampleFunctions

#endif
