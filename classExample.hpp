#pragma once
#include <iostream>
/*
Classes and Structs are essentially exactly the same.
The one difference is that members of structs are public by default, but members
of Classes are private by default
*/

void classExample();

//******************************************************************************
struct MyStruct {
  // typically, Structs are used for very simple data structures
  int i;
  double d;
};
// note the semi-colon at the end of class/struct

// Private member variables and functions ("methods") can only be accessed from
// inside the class, but not from outside (i.e., "users" cannot see them) Public
// can be accessed from outside - this is the interface

// Note: Of course, this is not the best example of a complex number class - you
// can use one of the very many existing libraries. This is just a basic
// example.

struct ComplexNumber {
  // typically, Structs are used for very simple data structures
private:
  double m_real;
  double m_imag;

public:
  // This is a "constructor" - it has the same name as the class
  ComplexNumber(double in_real = 0.0, double in_imag = 0.0)
      : m_real(in_real),
        m_imag(in_imag) // this is an "initialiser" list
  {
    // this is the constructor body (often blank because of initialiser list)
  }

  // These are marked 'const', because they do not make any changes to class
  // members
  double get_real() const { return m_real; }
  double get_imag() const { return m_imag; }
  // These change the class members, so cannot be marked const
  void set_real(double in_real) { m_real = in_real; }
  void set_imag(double in_imag) { m_imag = in_imag; }

  double norm() const { return m_real * m_real + m_imag + m_imag; }

  // "static" in this case means the function can be accessed without having to
  // call
  static ComplexNumber add(const ComplexNumber &x, const ComplexNumber &y) {
    double real_part = x.get_real() + y.get_real();
    double imag_part = x.get_imag() + y.get_imag();
    return ComplexNumber{real_part, imag_part};
  }

  // we can also "overload" operators (+,-,*,/,+= etc.)
  // This allows nice code like y = a + b; instead of having to call the 'add'
  // function
  friend ComplexNumber operator+(const ComplexNumber &l,
                                 const ComplexNumber &r) {
    return add(l, r);
  }
};
