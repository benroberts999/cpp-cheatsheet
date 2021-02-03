#pragma once

// This is the simplest possible version of a template.
// Much much more can be done with templates - it is a little more advanced

//******************************************************************************
namespace ExampleTemplates {

// Templates solve the problem of writing multiple similar functions.
// A new version of this function will be written for you every time you call it
// with a new data type! Make computers do the repetitive work for us.
// Templates are very powerful, but can be tricky when they get more
// complicated; this is just the simplest example
// If we call this with a 'double', then Type=double
// If we call this with an 'int', then Type=int etc.
// Note: templates must be defined and implemented in the header file (for
// reasons)
template <typename Type> Type add(Type value1, Type value2) {
  const Type result = value1 + value2;
  return result;
}

} // namespace ExampleTemplates
