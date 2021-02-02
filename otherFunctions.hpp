#pragma once
// ""#pragma once" is an automatic header guard.
// Technically, it is not "standard", so it is often discouraged.
// But it is supported by all the major compilers, and it much nicer

// A header file defines the functions, but does not implement them

//******************************************************************************
namespace OtherFunctions {

// By placing this in a different "namespace" I can have two functions with the
// same name. This is useful in large projects
double multiply(double x1, double x2);

} // namespace OtherFunctions
