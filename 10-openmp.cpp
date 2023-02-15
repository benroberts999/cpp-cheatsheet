#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>

double example_function(double x) {
  return x * x; // just an example
}

int main() {

  const int nthreads = omp_get_max_threads();

  std::cout << "Current thread: " << omp_get_thread_num() << " - "
            << "Mumber of threads in use: " << omp_get_num_threads() << " - "
            << "Mumber of threads available: " << omp_get_max_threads() << '\n';

  std::cout << "\n Basic openMP example\n\n";

  std::cout << "Simple 'serial' for loop: (without openMP):\n\n";
  for (int i = 0; i < nthreads; ++i) {
    std::cout << "thread: " << omp_get_thread_num() << "/"
              << omp_get_num_threads() << "/" << omp_get_max_threads() << "\n";
  }
  std::cout << "\n";

  std::cout << "Simple *incorrect* 'parallel' loop: with openMP demonstrating "
               "race condition (BAD):\n\n";
#pragma omp parallel for
  for (int i = 0; i < nthreads; ++i) {
    // std::cout << "thread: " << omp_get_thread_num() << "/"
    //           << omp_get_num_threads() << "\n";
    std::cout << "thread: " << omp_get_thread_num() << "/"
              << omp_get_num_threads() << "/" << omp_get_max_threads() << "\n";
  }
  std::cout << "\n";

  std::cout << "Simple parallel loop: with #pragma omp and 'critical':\n\n";
#pragma omp parallel for
  for (int i = 0; i < nthreads; ++i) {
#pragma omp critical
    std::cout << "thread: " << omp_get_thread_num() << "/"
              << omp_get_num_threads() << "/" << omp_get_max_threads() << "\n";
  }
  std::cout << "\n";
  std::cout
      << "Note: critical esnures that part of the code is only executed on one "
         "thread at a time - nb: avoid using critical (it should be a "
         "last resort), as it will likely throw away much of the benefit "
         "of using parallel!\n\n";

  //============================================================================

  std::cout << "Example: calculate f(x) for x=[0,10] in 1000 steps:\n";
  std::size_t n_steps = 10000;
  // size_t is the 'type' of the size() of vector - it is 'unsigned long int'

  // NOTE: in such a simple example, you're unlikely to actually see any
  // speed-up. Parallelisation adds some overhead to the code. You should always
  // time and tests your programs.

  std::vector<double> values;
  values.resize(n_steps);
  // We cannot use push_back inside parallel region, since we can't 'resize' the
  // same vector from two threads at the same time.

#pragma omp parallel for
  for (std::size_t i = 0; i < n_steps; ++i) {
    double x = 10.0 * (double(i) / double(n_steps));
    // NOTE: double x = 10.0 * (i / n_steps); would always zero.
    // Can you see why? Very common mistake!
    values.at(i) = example_function(x);
  }

  double sum_serial = 0.0;
  for (std::size_t i = 0; i < n_steps; ++i) {
    sum_serial += values.at(i);
  }

  // This loop contains a "race condition". Can you spot it?
  // this is a common mistake when using openMP.
  // It may try to write to the variable 'sum_bad' at the same time from two
  // threads
  // The answer will likely be incorrect. Worse, it will be random
  double sum_bad = 0.0;
#pragma omp parallel for
  for (std::size_t i = 0; i < n_steps; ++i) {
    sum_bad += values.at(i);
  }

  // Using a 'omp critical' condition solves this problem, but is not the most
  // efficient way to go
  double sum_good = 0.0;
#pragma omp parallel for
  for (std::size_t i = 0; i < n_steps; ++i) {
#pragma omp critical
    sum_good += values.at(i);
  }

  // Summing numbers is so common, there is a built-in method to do this:
  double sum_better = 0.0;
#pragma omp parallel for reduction(+ : sum_better)
  for (std::size_t i = 0; i < n_steps; ++i) {
    sum_better += values.at(i);
  }

  std::cout << sum_bad << "\n";
  std::cout << sum_good << "\n";
  std::cout << sum_better << "\n";
}