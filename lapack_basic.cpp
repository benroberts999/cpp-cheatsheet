#include <iostream>
#include <vector>

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
// General lapack documentation:
// http://www.netlib.org/lapack/explore-html/index.html
extern int dgeev_(char *, char *, int *, double *, int *, double *, double *,
                  double *, int *, double *, int *, double *, int *, int *);
}

int main() {

  // Define a 3x3 matrix with elements: Mij = 1/(i+j-1)
  int dimension = 4;
  // I will use std::vector to store matrix - this allows us to not have to
  // allocate/de-allocate memory ourselves
  std::vector<double> matrix;
  matrix.reserve(dimension * dimension);
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      // the 'double' is not required, since double/int => double
      // but I prefer to make this explicit
      matrix.push_back(1.0 / double(i + j + 1));
    }
  }

  std::cout << "Matrix:\n";
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      printf("%6.4f ", matrix.at(i * dimension + j));
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  // Normally, you would wrap all of this into a function/class
  //****************************************************************************
  // Data required by dgeev
  // See: http://www.netlib.org/lapack/explore-html/index.html
  char jobvl = 'N';
  char jobvr = 'N';
  std::vector<double> eigReal(dimension);
  std::vector<double> eigImag(dimension);
  double vl, vr;
  int ldvl = 1;
  int ldvr = 1;
  int lwork = 6 * dimension;
  std::vector<double> work(lwork);
  int info;

  // calculate eigenvalues using the DGEEV subroutine
  dgeev_(&jobvl, &jobvr, &dimension, matrix.data(), &dimension, eigReal.data(),
         eigImag.data(), &vl, &ldvl, &vr, &ldvr, work.data(), &lwork, &info);

  // check for errors
  if (info != 0) {
    std::cout << "Oops: dgeev returned error code " << info << '\n';
    return -1;
  }
  //****************************************************************************

  // Note that dgeev_ is destructive: matrix is killed to death
  std::cout << "Matrix, after being mauled to death by dgeev_:\n";
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      printf("%6.4f ", matrix.at(i * dimension + j));
    }
    std::cout << '\n';
  }
  std::cout << '\n';

  // output eigenvalues to stdout
  std::cout << "Eigenvalues:\n";
  for (int i = 0; i < dimension; i++) {
    printf("%.7e %+.7e i\n", eigReal[i], eigImag[i]);
  }
  std::cout << '\n';

  // 20 digits of expected results (from Mathematica)
  const std::vector<double> expected{
      1.5002142800592426219, 0.16914122022145006152, 0.0067382736057607500735,
      0.000096702304022629537237};

  std::cout << "Difference from expected (real part):\n";
  for (int i = 0; i < dimension; i++) {
    auto error = eigReal[i] - expected[i];
    printf("%.1e\n", error);
    if (std::abs(error) > 1.0e-15) {
      std::cout << "!!\n";
    }
  }

  return 0;
}
