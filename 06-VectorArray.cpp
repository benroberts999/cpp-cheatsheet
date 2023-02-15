#include <algorithm> // for for_each
#include <array>     // for final example
#include <cassert>   // for assert()
#include <iostream>
#include <numeric> // for accumulate
#include <string>
#include <vector>
// intractive example: https://godbolt.org/z/e1doToKqT

int main() {
  // std::vector is the c++ workhorse. It is a dynamically allocated,
  // resizable array data is stored in contiguous block (good for speed +
  // needed for libraries) Is completely compatible with regular c-style
  // arrays

  // Create a vector of ints (can be of any type)
  std::vector<int> a{1, 2, 3, 4, 5};

  // add elements to the vector:
  a.push_back(6);
  a.push_back(7);
  a.push_back(8);

  // can also just 'resize' the vector - which will fill with zeros
  std::cout << "Old size: " << a.size() << "\n";
  a.resize(10);
  std::cout << "New size: " << a.size() << "\n";

  // Loop through vector using a "ranged for loop"
  // This should be the standard way you use
  std::cout << "Ranged for loop:\n";
  for (int element : a) {
    std::cout << element << "\n";
  }

  // Using array index, with range checking:
  std::cout << "Access elements with range checking:\n";
  for (unsigned int i = 0; i < a.size(); ++i) {
    std::cout << a.at(i) << "\n";
  }

  // Using array index, WITHOUT range checking (don't do this):
  std::cout << "Array index [] - no range checking:\n";
  for (unsigned int i = 0; i < a.size(); ++i) {
    std::cout << a[i] << "\n";
    // nb: this is dangerous, a[11] is accessing passed end of vector!
  }

  // using itterators (note 'auto' keyword here saves annoying typing)
  // Rarely need to use this directly
  std::cout << "Iterators:\n";
  for (auto it = a.begin(); it != a.end(); ++it) {
    std::cout << *it << "\n";
  }

  // Using one of the standard algorithms, with a lambda function
  // This algorith applies the "lambda" (inline defined function) to each
  // element
  // nb: lambdas have weird '[](){}' syntax
  std::cout << "standard algorithm:\n";
  auto my_lambda = [](int el) { std::cout << el << "\n"; };
  std::for_each(a.begin(), a.end(), my_lambda);
  // There are thousands of very useful algorithms in <algorithm> and
  // <numeric> headers
  // Note: could put lambda definition in directly: some prefer this
  std::for_each(a.begin(), a.end(), [](int el) { std::cout << el << "\n"; });

  // Loop through vector, and modify its elements
  // We can use any of the above methods
  // Note: we need to take elements by reference to modify them
  std::cout << "Multiply all elements by two:\n";
  for (int &element : a) {
    element *= 2;
  }
  // now output again:
  for (int element : a) {
    std::cout << element << "\n";
  }

  // To interface with c or FORTRAN libraries, you might want acess to the raw
  // underying c-style array You can get this in two ways 1) a pointer to the
  // first element is the same as a pointer to the array, so
  int *pointer_to_array_1 = &a[0];
  // 2) use the .data() function, which was specifically designed for this:
  int *pointer_to_array_2 = a.data();
  assert(pointer_to_array_1 == pointer_to_array_2);

  for (std::size_t i = 0; i < a.size(); ++i) {
    // Directly access underlying c-style array
    std::cout << pointer_to_array_2[i] << "\n";
  }
  // nb: 'std::size_t' is the type of the size() and index for vectors.
  //  It is a 'long unsigned int'. It's mostly OK to just use 'int' here

  // sum all the items, using standard algorithm, accumulate
  //  (in numeric header)
  auto sum = std::accumulate(a.begin(), a.end(), 0);
  std::cout << "Sum=" << sum << "\n";

  // Note: these algorithms also work with any type:
  std::vector<std::string> b = {"a", "vector", "of", "strings"};
  auto words = std::accumulate(b.begin(), b.end(), std::string("words:"));
  std::cout << "words=" << words << "\n";

  // This is a vector of 'int'. The <> brackets are because vector is a
  // template, and can be instatuiated with any type, including user-defined
  // types (see class example)
  std::vector<int> v{4, 3, 7, 9, 12, 15};
  // We can add more elements:
  v.push_back(9);
  v.push_back(1);
  v.push_back(4);

  /*
  Performance note:
  If you know in advance how many elements you will need in your vector, you can
  call:
    v.reserve(_number_); // _number_ is number of elements needed
  This tells the compiler how much memory to allocate - which saves time,
  since the memory in 'vector' is gurenteed to be contiguous (all in a single
  block), which means if you add too many elements the entire vector might have
  to be moved to a new memory location.
  */

  // can loop through in multiple ways:
  for (std::size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ", ";
  }
  std::cout << "\n";

  for (auto it = v.begin(); it != v.end(); ++it) {
    // begin() returns an 'iterator' - which is much like a pointer:
    std::cout << *it << ", ";
  }
  std::cout << "\n";

  // The nicest way is with a ranged-for loop
  for (auto &x : v) {
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // or, be super fancy, and use an std algorithm with a lambda
  std::for_each(v.begin(), v.end(), [](int &x) { std::cout << x << ", "; });
  std::cout << "\n";

  std::cout << "\nSome algorithms\n";

  // accumulate (in <numeric> header) will add all values (to an initial value)
  auto result = std::accumulate(v.begin(), v.end(), 0.0);
  std::cout << "Sum: " << result << "\n";

  auto max_itr = std::max_element(v.begin(), v.end());
  // note: returns an iterator (like pointer) to the max element, not the
  // element itself:
  std::cout << "max element at: " << std::distance(v.begin(), max_itr) << '\n';
  std::cout << "max value: " << *max_itr << '\n';

  // sort:
  std::cout << "Sort the vector:\n";
  std::sort(v.begin(), v.end());

  for (auto &x : v) {
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // Use a lambda to change to condition used to sort
  std::cout << "Sort the vector, backwards:\n";
  std::sort(v.begin(), v.end(), [](int a, int b) { return b < a; });

  for (auto &x : v) {
    std::cout << x << ", ";
  }
  std::cout << "\n";

  std::cout << "\nstd array: a fixed-sized array of contiguous memory\n";
  // We must tell the compiler the size of the array, at compile time
  std::array<int, 5> a{1, 2, 3, 4, 5};
  for (auto &x : a) {
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // The algorthms work for vectors, arrays, and other "containers"
  auto max_itr_array = std::max_element(a.begin(), a.end());
  std::cout << "max array element at: "
            << std::distance(a.begin(), max_itr_array) << '\n';
  std::cout << "max array value: " << *max_itr_array << '\n';

  // For STATIC arrays (that is, arrays where the number of elements are known
  // at compile time), you can use std::array instead
  // Works almost exactly the same as the above, except it cannot be resized,
  // and the number of elements is a compile-time parameter:

  std::array<int, 5> array1{1, 2, 3, 4, 5};
  // std::array array2{1, 2, 3, 4, 5}; //with c++17, types can be deduced
  for (auto element : array1) {
    std::cout << element << "\n";
  }
}
