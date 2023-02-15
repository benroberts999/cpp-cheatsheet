

#include <iostream>

namespace MyNamespace {
void function1(int i) {
  // just example:
  std::cout << "MyNamespace::function1(" << i << ")\n ";
}
} // namespace MyNamespace

namespace MyOtherNamespace {
void function1(int i) {
  // just example:
  std::cout << "MyOtherNamespace::function1(" << i << ")\n ";
}
} // namespace MyOtherNamespace

int main() {
  // These functions have the same name, but that's OK, because they're in
  // different namespaces
  MyNamespace::function1(1);
  MyOtherNamespace::function1(1);
}