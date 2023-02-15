#include "06-templates.hpp"
#include <iostream>
#include <string>

// templates must either be included directly in the cpp file they are used, or
// in a header file. They cannot be placed in a seperate .cpp file.
int main() {

  //
  int i = 1;
  int j = 2;
  std::cout << " " << i << " + " << j << " = " << add(i, j) << "\n";

  double x = 1.1;
  double y = 2.2;
  std::cout << " " << x << " + " << y << " = " << add(x, y) << "\n";

  std::string s1 = "hello";
  std::string s2 = "wordl";
  std::cout << " " << s1 << " + " << s2 << " = " << add(s1, s2) << "\n";
}