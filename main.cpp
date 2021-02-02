#include <iostream> // for basic in/out (cout)
#include <string>   // for strings
// We must 'include' the header files for any other files we use
// Note: NEVER '#include' a .cpp file
#include "VectorArraySTL.hpp"
#include "classExample.hpp"
#include "functions.hpp"
#include "otherFunctions.hpp"
#include "templates.hpp"

// Every c++ project must have 1 (and only 1 "main" function)
// This is what's run when you execute your code.
// It may take command-line arguments; for this example we will ignore them

int main() {

  std::cout << "Hello world!\n";

  // This is a comment

  /*
    This is a
    comment that
    last many lines.
  */

  //****************************************************************************
  // Basic types:

  std::cout << "\nSome basic inbuilt types and examples:\n";
  // There are many ways to initialise a variable
  double d1 = 5.67;
  double d2{3.991};
  double d3 = d1 + d2;
  std::cout << "doubles: " << d1 << " " << d2 << " " << d3 << "\n";

  float f1 = 7.2f; // the 'f' here is optional, but makes '7.2' a float literal
  std::cout << "float: " << f1 << "\n";

  int i1 = 65;
  std::cout << "integer: " << i1 << "\n";

  // char's are stored as integers (ASCII) - and we can "cast" (convert
  // types) between them.
  char a1 = 'A';
  std::cout << a1 << " " << static_cast<int>(a1) << "\n";
  // We'll see how to deal with strings (multiple characters) later

  // Note: be very careful
  double result = 3 / 5;
  std::cout << "Result: " << result << "\n";

  double result2 = 3.0 / 5;
  std::cout << "Result2: " << result2 << "\n";

  // const:
  // If you know a value will never change, it's a good idea to mark it as
  // 'const' - it reduces chance of making errors
  double variable_pi = 3.14159;
  const double const_pi = 3.14159;
  variable_pi = 3.0;

  std::cout << "const: " << const_pi << " " << variable_pi << "\n";

  // Note: this would not compile:
  // const_pi = 3.0;

  //****************************************************************************
  // Scope:
  std::cout << "\nVariables are only defined in their scope!\n";
  // Usually, scopes are typically defined by curly braces:

  int var1 = 6;
  {
    int var2 = 7;
    // this works:
    std::cout << var1 << " " << var2 << "\n";
  }
  // this works:
  std::cout << var1 << "\n";
  // this would NOT work:
  // std::cout << var1 << " " << var2 << "\n";

  //****************************************************************************
  // boolean, if statements
  std::cout << "\nSome basic if statements:\n";

  bool is_equal = (3 == 3);
  if (is_equal) {
    std::cout << "Yay, 3 = 3\n";
  } else {
    std::cout << "Oh no!\n";
  }

  if (5 > 3) {
    std::cout << "Yay, 5 > 3\n";
  } else {
    std::cout << "Oh no!\n";
  }

  //****************************************************************************
  // for loops
  std::cout << "\nFor loops:\n";
  for (int i = 0; i < 10; ++i) {
    // ++i means i = i + 1;
    std::cout << i << ", ";
  }
  std::cout << "\n";

  //****************************************************************************
  // Strings:
  std::string text1{"This is a string."};
  std::cout << "\n" << text1 << "\n";

  std::string text2{"Purple monkey dishwasher"};
  std::string concat = text1 + " " + text2;
  std::cout << concat << "\n";

  // Make a subtring
  std::string sub_str = text2.substr(7, 6);
  // From position 7, with length 6
  std::cout << sub_str << "\n";

  // "size_t" is the type of the 'size' (length) of a string - it is an alias
  // for "unsigned long int"
  std::size_t pos = text1.find("a");
  std::string first_part = text1.substr(0, pos);
  std::string last_part = text1.substr(pos);
  std::cout << first_part << "\n" << last_part << "\n";

  // Example of a ranged-based for loop: super handy and readable
  for (char c : text1) {
    std::cout << c << "\n";
  }

  // This is the old long way of doing the above:
  for (std::size_t index = 0; index < text1.length(); ++index) {
    std::cout << text1[index] << "\n";
  }

  //****************************************************************************
  // auto: The compiler can usually work out for us what type something should
  // be:

  auto value1 = d1 * d2; // this will be a double
  auto value2 = i1 + 7;  // this will be an int
  std::cout << "\nauto: " << value1 << " " << value2 << "\n";

  // auto is extremely useful when dealing with values returned from a function.
  // What type should my variable be? Just make it the same as what is returned
  // by the function! Especially useful when dealing with complicated types that
  // arise in c++

  // Example: what type does .find() return from our string example?
  // Let the compiler work it out:
  auto pos2 = text1.find("a");
  std::cout << pos << " " << pos2 << "\n";

  //****************************************************************************
  //
  std::cout << "\nReferences and pointers:\n";
  int my_integer = 3;

  // Create a 'reference' to a variable:
  int &my_reference = my_integer;
  std::cout << my_integer << " " << my_reference << "\n";
  my_integer = 4;
  std::cout << my_integer << " " << my_reference << "\n";
  my_reference = 5;
  std::cout << my_integer << " " << my_reference << "\n";
  // This seems pretty useless - and in this context it is.
  // However, references are useful for passing parameters into functions,
  // especially when those parameters are large objects (e.g., a matrix) that we
  // do not want to copy - see "functions" examples

  // Get the memory address of a variable, with '&'
  // Note: in this context, it has different meaning than the referennce '&'
  std::cout << &my_integer << "\n";
  // store the memory address in a pointer:
  int *my_pointer = &my_integer;
  // Note: the type here is 'pointer to integer'
  std::cout << "Pointer: " << my_pointer << "\n";
  // Access the variable stored in that memory address:
  // This is called "dereferenceing" the pointer:
  std::cout << "Value pointer points to: " << *my_pointer << "\n";
  // We can update the value:
  *my_pointer = 6;
  std::cout << "Pointer: " << my_pointer
            << ", Value pointer points to: " << *my_pointer << "\n";
  // Note: the pointer didn't change, just the value

  // We can also make this pointer "point" to a different value:
  int my_integer2 = 27;
  my_pointer = &my_integer2;
  std::cout << "Pointer: " << my_pointer
            << ", Value pointer points to: " << *my_pointer << "\n";
  // Note: the pointer changed

  //****************************************************************************
  // Use some functions, basic template, and namespaces:
  // These functions are defined in the files: src/functions,
  // src/otherFunctions, src/templates.
  // See those files for explanation of namespace, overload
  std::cout << "\nFunctions, namespaces, templates:\n";

  auto res1 = ExampleFunctions::multiply(d1, d2);
  std::cout << res1 << "\n";

  // "function overloading"
  auto res2 = ExampleFunctions::multiply(i1, i1);
  std::cout << res2 << "\n";

  // use different namespace
  auto res3 = OtherFunctions::multiply(d1, d2);
  std::cout << res3 << "\n";

  // use template
  auto res4 = ExampleTemplates::add(3.75, 6.41);
  auto res5 = ExampleTemplates::add(3, 6);
  std::cout << res4 << " " << res5 << "\n";

  // pass by value (copy) - this is the default
  int my_2nd_int = 6;
  std::cout << "Before: " << my_2nd_int << "\n";
  ExampleFunctions::printValue(my_2nd_int);
  std::cout << "After: " << my_2nd_int << "\n";

  // pass by reference
  std::cout << "Before: " << my_2nd_int << "\n";
  ExampleFunctions::modifyValue(my_2nd_int);
  std::cout << "After: " << my_2nd_int << "\n";

  // pass by const reference
  std::cout << "Before: " << my_2nd_int << "\n";
  ExampleFunctions::dontModify(my_2nd_int);
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

  //****************************************************************************
  // Vectors, arrays, and STL (STL = c++ standard libraries)

  VectorArraySTL_example();

  classExample();

  return 0;
}
