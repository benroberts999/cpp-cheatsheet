#include <iostream>

/*
This shows an example of using a static variable in a function.
It's extr
*/

void func_normal() {
  // this will be a NEW variable each time the function is called
  int a = 3;
  a += 1;
  std::cout << a << "\n";
}

void func_static() {
  // this will be the SAME variable each time the function is called
  // 'a' will be initialised once, the first time this function is called
  // Very rare to need static variables, and they have a small performace cost
  // as program needs to check each time if already initialised.
  // They can also be problematic, as they can make code difficult to debug.
  static int a = 3;
  a += 1;
  std::cout << a << "\n";
  func_normal();
}

int main() {

  int n_loop = 6;

  std::cout << "Call func_normal() from loop:\n";
  for (int i = 0; i < n_loop; ++i) {
    func_normal();
  }

  std::cout << "Call func_static() from loop:\n";
  for (int i = 0; i < n_loop; ++i) {
    func_static();
  }
}
