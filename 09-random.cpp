#include <iostream>
#include <random>

/*
This is a basic example for generating random numbers in c++
*/

int main() {
  std::cout << "\nRandom numbers:\n";

  // random_device produces uniformly-distributed random (unsigned) integers.
  // It does not need to be seeded (happens automatically).
  // It is implementation specific.
  // We usually use this to only to seed a better random number generator

  std::cout << "1) random_device : simplest random integer generator.\n";
  std::random_device rd;

  std::cout << "Generates random ints between: min()="
            << std::random_device::min()
            << ", and max()=" << std::random_device::max() << "\n";

  std::cout << "\nCall random_device() 10 times:\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << rd() << "\n";
  }

  // random_device may be suitable for many cases, but more sophisticated
  // engines are provided. The mt19937 (AKA mersenne_twister_engine) is such an
  // engine based on the Mersenne Twister algorithm, and produces high-quality
  // random integers (unsigned long).
  // It must be seeded; typically, this is done using random_device:

  std::cout << "\n2) std::mt19937 (mersenne_twister_engine) - better random "
               "numbers.\n"
            << "Must be seeded - can seed w/ a constant to get deterministic "
               "results\n";

  bool deterministic = false;
  // Use random_device to seed mt19937, if we want. Otherwise set the seed to
  // "12345"
  int seed;
  if (deterministic) {
    seed = 12345;
  } else {
    seed = rd();
  }

  // This can also be done in one line:
  // auto seed = deterministic ? 12345 : rd();
  std::mt19937 mt_generator(seed);

  std::cout << "\nCall mt19937() 10 times:\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << mt_generator() << "\n";
  }

  std::cout << "\n3) get more useful random numbers, using a *distribution*:\n";

  std::cout << "\n - uniform_real_distribution [-10,10]:\n";
  // Define distribtuion of real (double) numbers between (-10,10):
  std::uniform_real_distribution<double> uniform_rn(-10.0, 10.0);
  // Pass the generator to this distribution to extract numbers.
  for (int i = 0; i < 10; ++i) {
    std::cout << uniform_rn(mt_generator) << "\n";
  }

  std::cout << "\n - normal_distribution [mean=0, sd=0.1]:\n";
  // Gaussian (normal) distribution, with mean 0, standard deviation 0.1:
  std::normal_distribution<double> Gauss_rn(0.0, 0.1);
  for (int i = 0; i < 10; ++i) {
    std::cout << Gauss_rn(mt_generator) << "\n";
  }
}
