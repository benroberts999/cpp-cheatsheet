#include "random.hpp"
#include <iostream>
#include <random>

void random_examples() {

  std::cout << "\nRandom numbers:\n";

  // random_device produces uniformly-distributed random (unsigned) integers.
  // It does not need to be seeded (happens automatically).
  // It is implementation specific.
  std::random_device rd;

  std::cout << "random_device, min() and max():\n";
  std::cout << std::random_device::min() << " " << std::random_device::max()
            << "\n";
  std::cout << "random_device:\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << rd() << "\n";
  }

  // random_device may be suitable for many cases, but more sophisticated
  // engines are provided. The mt19937 (AKA mersenne_twister_engine) is such an
  // engine based on the Mersenne Twister algorithm, and produces high-quality
  // random integers (unsigned long).
  // It must be seeded; typically, this is done using random_device:
  std::mt19937 mt_generator(rd());

  std::cout << "\nmt19937:\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << mt_generator() << "\n";
  }

  // The get more useful random numbers, you will use a _distribution_
  // Several are provided, the most comman are:
  // uniform_real_distribution, uniform_int_distribution, and
  // normal_distribution
  // The usage is: first, define the distribution needed; then combine the
  // generator with the distribution to get the required random number:

  std::cout << "\nuniform_real_distribution:\n";
  // Define distribtuion of real (double) numbers between (-10,10):
  std::uniform_real_distribution<double> uniform_rn(-10.0, 10.0);
  // Pass the generator to this distribution to extract numbers.
  for (int i = 0; i < 10; ++i) {
    std::cout << uniform_rn(mt_generator) << "\n";
  }

  std::cout << "\nnormal_distribution:\n";
  // Gaussian (normal) distribution, with mean 0, standard deviation 1.0:
  std::normal_distribution<double> Gauss_rn(0.0, 1.0);
  for (int i = 0; i < 10; ++i) {
    std::cout << Gauss_rn(mt_generator) << "\n";
  }
}
