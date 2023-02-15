#include <fstream>
#include <iostream>
// #include <cmath>
// #include <vector>

//--------------------------------------------------------------------------
// We can put the function "declarations" (sort of like "placeholders")
// at the top of the code, and then put the full definitions for those functions
// after "main()".
// Equivalently, you can just put your main() function at the end, but this can
// look a bit messier.
// Or, we can separate these functions into a sepperate c++ file, but for a
// small project that isn't necisary.

// Make a simple struct to hold the coordinates
struct Coords {
  double x;
  double v;
};

struct Parameters {
  double mass;
  double k_spring;
  double b_damp;
};

// ODE function declaration: outputs the gradient of the coupled system of ODEs
Coords ODE_gradiant(const Coords &xv_old, const Parameters &params);

// declarations - operator overloading
// provide operator to allow us to 'cout' the Coords
std::ostream &operator<<(std::ostream &ostr, const Coords &vect);
// operator that will multiply Coords by a double
Coords operator*(double a, Coords b);
Coords operator*(Coords b, double a) { return a * b; }
// operator that will add two coordinate vectors
Coords &operator+=(Coords &a, const Coords &b);
Coords operator+(Coords a, const Coords &b) { return a += b; }

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

int main() {

  // Simulation parameters: step size, simulation length
  const double dt = 0.1;
  const int N = 1000;

  // Initial conditions of the simulation: position and velocity
  Coords coords{10.0, 0.0};

  Parameters params;
  params.mass = 1.0;
  params.k_spring = 0.1;
  params.b_damp = 0.05;
  // could also write:
  // Parameters params{1.0, 0.1, 0.05};

  // output to the console using the overloading of operator<< for Coords
  std::cout << coords << '\n';

  // Step forward, in N steps of dt, to solve the ODE:
  for (int i = 0; i < N; i++) {
    // Integration steps
    coords += dt * ODE_gradiant(coords, params);

    // Print out new co-ordinates
    std::cout << coords << '\n';
  }

  return 0;
}

//--------------------------------------------------------------------------
// Computes the derivative of the system of ODEs from old_coords
Coords ODE_gradiant(const Coords &coords, const Parameters &params) {

  // Solve a damped harmonic oscillator:
  // m*dx^2/dt^2 + b*dx/dt + k*x = 0

  // Coupled ODE equations:
  Coords gradient_kn;
  gradient_kn.x = coords.v;
  gradient_kn.v =
      (-params.k_spring * coords.x - params.b_damp * coords.v) / params.mass;
  return gradient_kn;
}

//--------------------------------------------------------------------------
// Takes output stream, ostr, and appends the content of a Coords vector,
// xv, onto the end. Notice that it has the '&' at the front. This means it
// will CHANGE ostr at the memory level, i.e. it can't be undone.
std::ostream &operator<<(std::ostream &ostr, const Coords &xv) {
  ostr << xv.x << ' ' << xv.v;
  return ostr;
}

//--------------------------------------------------------------------------
// Double * Coords multiplication
// Makes a copy of the vector b, multiplies each element by a and then returns
// it back.
Coords operator*(double a, Coords b) {
  b.x *= a;
  b.v *= a;
  return b;
}

//--------------------------------------------------------------------------
// Adds two Coords vectors
Coords &operator+=(Coords &a, const Coords &delta_a) {
  a.x += delta_a.x;
  a.v += delta_a.v;
  return a;
}
