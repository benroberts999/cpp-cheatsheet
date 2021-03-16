#include "VectorArraySTL.hpp"
#include <algorithm> // sort, find (and many many more)
#include <array>
#include <iostream>
#include <numeric> // accumulate, adjacent_difference (and many many more)
#include <vector>

void VectorArraySTL_example() {

  // There are many many standard "containers" (data structures) provided by the
  // c++ standard library, including map, list, set etc. etc.
  // Generally speaking, std::vector should be the default

  std::cout << "\nstd vector: a variable-sized array of contiguous memory\n";

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
}
