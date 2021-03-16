#include "classExample.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

void classExample() {

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
