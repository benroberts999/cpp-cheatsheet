#include <algorithm>
#include <iostream>
#include <vector>

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

class ComplexNumber {
  // typically, classes are used for cases with member functions
private:
  double m_real;
  double m_imag;

public:
  // This is a "constructor" - it has the same name as the class
  ComplexNumber(double in_real = 0.0, double in_imag = 0.0)
      : m_real(in_real), m_imag(in_imag) // this is an "initialiser" list
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

//******************************************************************************
int main() {

  std::cout << "\nStruct and Class examples:\n";

  MyStruct s1{3, 6.5};
  std::cout << "A struct: " << s1.i << " " << s1.d << "\n";
  // can update
  s1.i = 7;
  std::cout << s1.i << " " << s1.d << "\n";

  // Lets use the ComplexNumber class as an example

  ComplexNumber c1{2.0, 6.5};
  std::cout << "A class: c1 = " << c1.get_real() << " +i" << c1.get_imag()
            << "\n";
  c1.set_real(5.0);
  c1.set_imag(14.5);
  std::cout << "Now, c1 = " << c1.get_real() << " +i" << c1.get_imag() << "\n";

  const ComplexNumber c2{3.1, 1.6};
  std::cout << "c2 = " << c2.get_real() << " +i" << c2.get_imag() << "\n";
  // Note: we may not call 'set' functions on a const ComplexNumber, since these
  // functions were not marked const! We cannot change a const variable!
  // c2.set_real(1.0); //this would not compile

  auto c3 = ComplexNumber::add(c1, c2); // old boring C way
  std::cout << "Use operator overloading:\n";
  auto c4 = c1 + c2; // nice c++ way
  std::cout << "c3 = " << c3.get_real() << " +i" << c3.get_imag() << "\n";
  std::cout << "c4 = " << c4.get_real() << " +i" << c4.get_imag() << "\n";

  std::cout << "Make a vector of ComplexNumber class objects:\n";
  std::vector<ComplexNumber> vec{c1, c2, c3, c4};

  for (const auto &cn : vec) {
    std::cout << "cn = " << cn.get_real() << " +i" << cn.get_imag() << "\n";
  }

  std::cout << "Use algorithms with our class objects:\n";
  // This is where lambdas really shine
  // Write lambdas to compare our complex numbers by imag, and norm:
  auto comp_imag = [](ComplexNumber x, ComplexNumber y) {
    return x.get_imag() < y.get_imag();
  };
  auto comp_norm = [](ComplexNumber x, ComplexNumber y) {
    return x.norm() < y.norm();
  };

  auto max_norm = std::max_element(vec.begin(), vec.end(), comp_norm);
  std::cout << "Max element (by norm) = " << max_norm->get_real() << " +i"
            << max_norm->get_imag() << "\n";
  // Note" a->b(); is short-cut notation for (*a).b();
  // since 'max_norm' is an iterator (like pointer) we have to dereference it

  std::cout << "Sort by imaginary part:\n";
  std::sort(vec.begin(), vec.end(), comp_imag);
  for (const auto &cn : vec) {
    std::cout << "cn = " << cn.get_real() << " +i" << cn.get_imag() << "\n";
  }
}
