#include <algorithm> // for sort, for_each, max_element etc.
#include <iostream>
#include <numeric> // for std::accumulate
#include <vector>

int main() {
  std::cout << "According to textbook definition, a lambda is an 'anomymous' "
               "function object... \n"
            << "This is a confusion definition, since we can give them names.\n"
            << "I prefer to think of them as little functions we can define "
               "in-line.\n\n";

  // Lambdas use syntax:
  // [](){}
  // where:
  // [*captures*](*arguments*){*function body*}

  // 1. Simplest case: no 'captures', no arguments

  // If we name them, we *must* use the 'auto' keyword
  auto lambda1 = []() { return "hello"; };

  std::cout << lambda1() << '\n';

  auto lambda2 = []() { std::cout << "hello2\n"; };
  // call it:
  lambda2();

  // 2. no 'captures', but add arguments

  auto squarer = [](int i) { return i * i; };
  std::cout << squarer(1) << " " << squarer(2) << " " << squarer(3) << '\n';

  // 3. Captures: lambdas can capture local variable for use inside
  // They may capture by value (which is the default), or by reference
  // Usualy, we only capture by reference if we want to avoid copying a large
  // object

  int a = 1;
  int b = 1;

  auto lambda3 = [a]() { return a; };
  auto lambda4 = [&b]() {
    b++; // this is allowed, but not recommended
    return b;
  };

  std::cout << lambda3() << " " << lambda4() << '\n';
  std::cout << a << " " << b << '\n';

  // Usually, lambdas are used for very small functions, though they can be a
  // large as you like

  // Lambdas can be passed into certain functions as input
  // They are extremely useful for combining with standard algorithms

  // Create a vector of integers:
  std::vector<int> vec{3, 9, -2, 1, 5, -12, 66, 0, 12, -8};

  // add a few more:
  vec.push_back(14);
  vec.push_back(-1);

  std::cout << "Print elements, using 'ranged for loop'\n";

  for (auto element : vec) {
    std::cout << element << ", ";
  }
  std::cout << "\n\n";

  // Find the sum, using accumulate
  auto sum = std::accumulate(vec.begin(), vec.end(), 0);

  std::cout << "sum=" << sum << "\n\n";

  std::cout << "Sort the vector\n";

  std::sort(vec.begin(), vec.end());

  std::cout << "Print the elements, using a lambda\n";
  std::cout << "(see lambda.cpp for info on lambdas)\n";

  std::for_each(vec.begin(), vec.end(), [](int i) { std::cout << i << ", "; });
  std::cout << "\n\n";

  std::cout << "Sort the vector by absolute value, using a lambda:\n";

  std::sort(vec.begin(), vec.end(),
            [](int a, int b) { return std::abs(a) < std::abs(b); });

  // The above is equivilant to this, which is more readable:
  auto compare_by_abs = [](int a, int b) { return std::abs(a) < std::abs(b); };
  std::sort(vec.begin(), vec.end(), compare_by_abs);

  std::cout << "Print the elements\n";
  for (auto element : vec) {
    std::cout << element << ", ";
  }
  std::cout << "\n\n";
}