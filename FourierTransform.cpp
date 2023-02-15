#include <cmath>
#include <complex>
#include <fstream>
#include <gsl/gsl_fft_complex.h>
#include <iostream>
#include <vector>

// Full documentation: https://www.gnu.org/software/gsl/doc/html/fft.html

// Though note: that page uses C, not C++, so many of the operators are much
// more complicated in those notes. Much simpler in c++, since we can use
// std::vector and std::complex

int main(void) {

  const std::size_t n = 300;

  // Construct array of complex numbers to store.
  // (Even though input to FT is real, the FT is done _in place_, so this needs
  // to be an array of complex numbers.)
  std::vector<std::complex<double>> data(n);

  // Data: sum of few sin functions
  //(Possible to choose better example, where FT will be real)
  for (std::size_t i = 0; i < n; i++) {
    const auto phi = (double(i) / n) * (2.0 * M_PI);
    data.at(i) = 10.0 * std::sin(10.0 * phi) - 5.0 * std::sin(20.0 * phi) +
                 2.0 * std::sin(50.0 * phi);
  }

  // Allocate memory that GSL library uses:
  // 'wavetable' is a lookup table of sin/cosine values used to evaluate FFT
  // These can be re-used, so only need to be calc'd once - drastically
  // improving speed of calculation.
  // 'workspace' is memory we allocate that GSL needs to compte the FFT
  // nb: must remember to de-allocate (free) this memory when we're done
  // (because GSL is written in C, not c++, so it won't de-allocate for us)
  gsl_fft_complex_wavetable *wavetable = gsl_fft_complex_wavetable_alloc(n);
  gsl_fft_complex_workspace *workspace = gsl_fft_complex_workspace_alloc(n);

  // make a copy of the data.
  // Not actually required, but gsl_fft_complex_forward is destructive
  // (it calculates the FFT in place), so I store old data so I can plot it
  // together with the FT later
  auto data_ft = data;

  // This is the "weird" c++ part - we need to convert c++ "pointer to
  // std::complex<double>" to a "pointer to double" that the GSL (C) library can
  // understand - i.e., just a pointer to the first double in the array, which
  // is the real part of the first complex number. The std::vector function
  // .data() returns a pointer to first element (a complex<double>) in array.
  double *data_ft_ptr = reinterpret_cast<double *>(data_ft.data());
  // equivilant to this:
  // double *data_ft_ptr = reinterpret_cast<double *>(&data_ft[0]);

  // Unfortunately, we cannot do this:
  // double * data_ptr = &(data[0].real());
  // although it looks like we should be able to. Because .real() returns a
  // *copy* of the real part, not a reference, so this would be taking the
  // memory address of a temporary variable [it won't compile, so no chance of
  // mistake]

  // Use GSL to compte FT
  // nb: there are other functions we can use in spacial case that n is a power
  // of 2, which are much faster
  gsl_fft_complex_forward(data_ft_ptr, 1, n, wavetable, workspace);

  // free memory used to compute FFT (note: both can be re-used)
  gsl_fft_complex_wavetable_free(wavetable);
  gsl_fft_complex_workspace_free(workspace);

  // Plot the data and the (absolute value of the) FT(data) to a file.
  // I scale the FT by sqrt(n), just so it's easier to see on same scale
  std::ofstream out_file("data.txt");
  for (std::size_t i = 0; i < n; i++) {
    out_file << i << ' ' << data.at(i).real() << ' '
             << std::abs(data_ft.at(i)) / std::sqrt(n) << "\n";
  }
  // e.g., plot with gnuplot using:
  // plot "data.txt" u 1:2 w l t "data", "" u 1:3 w l t "|FT(data)|/sqrt(N)"

  return 0;
}
