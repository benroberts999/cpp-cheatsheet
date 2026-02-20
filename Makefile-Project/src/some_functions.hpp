#pragma once
// 'pragma once' is an automatic header guard.
// It's technically not "standard" c++, but is widely used

// Namespaces provide a method for preventing name conflicts in large projects.
// Functions (etc.) declared inside a 'namespace' are placed in a named scope
// that prevents them from being mistaken for identically-named functions in
// other scopes.
// Not required, but recommended
// note: 'std' in the namespace all the standard c++ library functions/classes
// are in
namespace my_functions {

int func1(int input);

int func2(int input);

} // namespace my_functions