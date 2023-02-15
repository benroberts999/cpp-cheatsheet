#include <cassert> // for assert(), used in matrix example
#include <iostream>
#include <vector>
// Interactive example: https://godbolt.org/z/MsfhEhGoE

//*****************************************************************************
// By far the worst part of c++ is that there is no standard built-in matrix
// In real world, we use one of many available libraries.
// However, we can write our own basic matrix class in just few lines
// I'm happy to just give students this code - but will go over it in first week
class Matrix {
private:
  // use a std::vector to store the data
  std::vector<double> m_data;
  // store the # of rows/cols
  int m_rows, m_cols;
  // I use 'm_' to signify these are member variables (just convention)

public:
  // contructor: contructs a matrix of dimension: rows X cols
  Matrix(int rows, int cols)
      : m_data(rows * cols), m_rows(rows), m_cols(cols) {}

  // note: this returns a reference to double, so we can modify the data
  double &at(int i, int j) {
    assert(i < m_rows && j < m_cols);
    return m_data[i * m_cols + j];
  }

  int rows() { return m_rows; }
  int cols() { return m_cols; }

  // to be fancy, we can also supply a '()' operator
  double &operator()(int i, int j) { return at(i, j); }

  // provide function that returns pointer to first element
  // (allows us to use this class as though it were a plain c-style array)
  double *data() {
    return m_data.data();
    // We used std::vector function data() here. It is equivilant to:
    // return &m_data[0];
  }
};

// We can also do 'fun' things, by overloading operators for the matrix
// example, provide a '+' operator: takes in two matrices, returns their sum
Matrix operator+(Matrix &a, Matrix &b) {
  Matrix sum = a;
  for (int i = 0; i < b.rows(); ++i) {
    for (int j = 0; j < b.cols(); ++j) {
      sum(i, j) += b(i, j);
    }
  }
  return sum;
  // Note: there are "better" ways to write a function like this, but this
  // will do for now
}

//*****************************************************************************
// Example for using LAPACK
// dsyev_ is a symbol in the LAPACK library files
// Documentation: http://www.netlib.org/lapack/explore-html/index.html
extern "C" {

extern int dsyev_(char *jobz, char *uplo, int *dimension, double *in_out_matrix,
                  int *dimension2, double *out_e_values,
                  double *workspace_array, int *workspace_size, int *info);

// The variable names in the declaration here are not required, but I find them
// helpful
//   extern int dsyev_(char *, char *, int *, double *, int *, double *,
//                     double *, int *, int *);
// LAPACK uses fortran, and in order to get c++ to talk to fortran we need to
// pass raw pointers to the data - LAPACK takes all values as pointers.
// extern "C"  essentially means we are calling an external (non c++) function
}

//*****************************************************************************
int main() {
  // construct a matrix, called m
  Matrix m{3, 3};
  // All the following are equivilant:
  // Matrix m(3,3);
  // auto m = Matrix(3,3);
  // Matrix m = Matrix(3,3);

  // Initialse values, such that m_ij = i+j (just example)
  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.cols(); ++j) {
      m(i, j) = i + j;
    }
  }

  std::cout << "Matrix m:\n";
  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.cols(); ++j) {
      std::cout << m(i, j) << " ";
    }
    std::cout << "\n";
  }

  // Note: by default, c++ knows how to make a copy of this matrix:
  Matrix m2 = m;
  std::cout << "m2 = m:\n";
  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.cols(); ++j) {
      std::cout << m2(i, j) << " ";
    }
    std::cout << "\n";
  }

  // create their sum
  auto m3 = m + m2;
  std::cout << "m3 = m + m2:\n";
  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.cols(); ++j) {
      std::cout << m3(i, j) << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  // Data required by dsyev. See documentation for description of each option:
  char jobz{'V'}; // tell LAPACK what to do
  char uplo{'U'}; // upper or lower part of symmetric matrix*
  // LAPACK uses fortran, which is column-major (c++ is row major), so U=L and
  // L=U this doesn't matter if we just fill the entire symmetric matrix
  int dimension = m.rows(); // square matrix, rows=cols=dimension
  // "workspace" - extra memory LAPACK needs to do its job
  int workspace_size = 6 * dimension;
  std::vector<double> work(workspace_size);
  int info;

  // create a vector to store the result (eigenvalues)
  std::vector<double> eigenvalues(dimension);
  // the eigen vectors will be stored in m (m will be over-written by LAPACK)
  // So, it's often good to make a copy of m before calling this:
  auto in_out_matrix = m;

  // calculate eigenvalues using the DSYEV lapack subroutine:
  dsyev_(&jobz, &uplo, &dimension, in_out_matrix.data(), &dimension,
         eigenvalues.data(), work.data(), &workspace_size, &info);

  // nb: I have to comment out the call to dsyev_, since compilerExplorer
  // doesn't have LAPACK installed, but this should work on your pc
  // Just don't forget to compile with -llapack (and maybe -lblas, depending
  // on compiler)

  std::cout << "Eigen values:\n";
  for (std::size_t i = 0; i < eigenvalues.size(); ++i) {
    std::cout << eigenvalues.at(i) << "\n";
  }

  std::cout << "\nEigen vectors:\n\n";
  for (int i = 0; i < in_out_matrix.rows(); ++i) {
    std::cout << "EVec for EVal: " << eigenvalues.at(i) << ":\n";
    for (int j = 0; j < in_out_matrix.cols(); ++j) {
      std::cout << in_out_matrix(i, j) << " ";
    }
    std::cout << "\n\n";
  }
}
