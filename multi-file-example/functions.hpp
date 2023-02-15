#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

// This ^ is a  header guard (also called an include guard).
// It ensures this header will only be included once per project

// Namespaces provide a method for preventing name conflicts in large projects.
// Functions (etc.) declared inside a 'namespace' are placed in a named scope
// that prevents them from being mistaken for identically-named functions in
// other scopes.
// Not required, but recommended
// note: 'std' in the namespace all the standard c++ library functions/classes
// are in
namespace functions {

int func1(int input);

int func2(int input);

} // namespace functions

#endif