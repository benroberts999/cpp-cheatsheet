#include <iostream>
#include <omp.h> //for omp_get_thread_num() etc.
#include <random>
#include <utility> // for std::pair (not needed on most compilers)

/*
Generating random numbers in parallel (eg, when using openMP) can be tricky.
This shows a few common mistakes, and how to avoid them.
*/

// This function is used in the last example
auto my_generator() {
  // static: will only be constructed ONCE, will live for life of program
  // nb: thread_local implies static: i.e., thread_local = static thread_local

  // nb:
  // "std::random_device{}()" is one-line version of:
  //   std::random_device rd;
  //   rd();

  thread_local std::mt19937 generator_tl(std::random_device{}());
  return generator_tl();
}

//============================================================================
//============================================================================
int main() {

  int n_loop = 6;

  //============================================================================

  std::cout << "\n Basic openMP example\n\n";

  std::cout << "Simple loop: without #pragma omp:\n";
  for (int i = 0; i < n_loop; ++i) {
    std::cout << "thread: " << omp_get_thread_num() << "/"
              << omp_get_num_threads() << "\n";
  }
  std::cout << "\n";

  std::cout << "Simple loop: with #pragma omp - race condition:\n";
#pragma omp parallel for
  for (int i = 0; i < n_loop; ++i) {
    std::cout << "thread: " << omp_get_thread_num() << "/"
              << omp_get_num_threads() << "\n";
  }
  std::cout << "\n";

  std::cout << "Simple loop: with #pragma omp - w. critical:\n";
  std::cout << "critical esnures that part of the code is only executed on one "
               "thread at a time - nb: avoid using critical (it should be a "
               "last resort), as it will likely throw away much of the benefit "
               "of using parallel!\n";
#pragma omp parallel for
  for (int i = 0; i < n_loop; ++i) {
#pragma omp critical
    std::cout << "thread: " << omp_get_thread_num() << "/"
              << omp_get_num_threads() << "\n";
  }
  std::cout << "\n";

  //============================================================================

  std::cout << "\nRandom number generation with OpenMP:\n\n";

  // make a generator, seed it using random_device
  std::mt19937 generator(std::random_device{}());

  std::cout << "Random numbers in parallel, with race condition:\n\n";
  std::cout
      << "The race condition is caused by each thread using the same random\n"
         "number generator - there is a chance two threads will try to do "
         "this\n"
         "at the same time, so they will get the _same_ random number (bad!)\n";

  // list to store calculated random numbers, and which thread
  std::vector<std::pair<int, int>> list(n_loop);
#pragma omp parallel for
  for (int i = 0; i < n_loop; ++i) {
    int thread = omp_get_thread_num();
    int rn = int(generator()); // returns 'long unsigned int', convert to int
    list.at(i) = std::pair<int, int>{thread, rn};
    // list.at(i) = {thread, rn}; // with c++17 we can deduce the type
  }

  // uses c++17 feature: structured bindings
  for (auto [thread, rand] : list) {
    std::cout << thread << ": " << rand << "\n";
  }
  std::cout << "\n";

  // structured bindings equivilant to this:
  for (const std::pair<int, int> &item : list) {
    int thread = item.first;
    int rand = item.second;
    std::cout << thread << ": " << rand << "\n";
  }
  std::cout << "\n";

  //============================================================================

  std::cout
      << "Random numbers in parallel, with thread_local (incorrectly):\n\n";
  std::cout
      << "We can avoid this race condition by declaring our generator to\n"
         "be `thread_local` - this means the variable will be stored\n"
         "seperately on each thread that initialises it.\n"
         "The problem with the way we do it here, is that only one thread "
         "initialises the generator, so the other threads don't have access\n";

  // nb: thread_local implies static: i.e., thread_local = static thread_local
  thread_local std::mt19937 generator_tl1(std::random_device{}());

#pragma omp parallel for
  for (int i = 0; i < n_loop; ++i) {
    int thread = omp_get_thread_num();
    int rn = int(generator_tl1());
    list.at(i) = {thread, rn};
  }

  for (auto [thread, rand] : list) {
    std::cout << thread << ": " << rand << "\n";
  }
  std::cout << "\n";

  std::cout << "Random numbers in parallel, with thread_local, method 1:\n\n";
  std::cout << "To correct this, we have to make this call _inside_ the "
               "parellel region:\n";
#pragma omp parallel
  {
    // nb: thread_local implies static: i.e., thread_local = static thread_local
    thread_local std::mt19937 generator_tl(std::random_device{}());
#pragma omp for
    for (int i = 0; i < n_loop; ++i) {
      int thread = omp_get_thread_num();
      int rn = int(generator_tl());
      list.at(i) = {thread, rn};
    }
  }

  for (auto [thread, rand] : list) {
    std::cout << thread << ": " << rand << "\n";
  }
  std::cout << "\n";

  //============================================================================

  std::cout << "Random numbers in parallel, with thread_local in function:\n\n";
  std::cout
      << "Making the call inside the parallel region can be annoying and\n"
         "limitting. Instead, we can wrap this in a new function that\n"
         "contains a thread_local variable. Thread_local variables are\n"
         "also static, meaning they will only be initialised ONCE, and\n"
         "then live for the life of the program. thread_local means it\n"
         "will be initialised once PER THREAD\n";
#pragma omp parallel for
  for (int i = 0; i < n_loop; ++i) {
    int thread = omp_get_thread_num();
    int rn = int(my_generator());
    list.at(i) = {thread, rn};
  }

  for (auto [thread, rand] : list) {
    std::cout << thread << ": " << rand << "\n";
  }
}
