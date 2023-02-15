# Super basic makefile for examples.
# A makefile is a basic way of compiling large c++ ptojects
# They are not required, and are a little 'overkill' for very small projects
# For cery large project, other build systems (CMake) are more favoured 
# (but are more complex)

CXX=g++
STD=-std=c++17
WARN=-Wall -Wextra -Wpedantic -Wconversion
OPT=-O3

EXECUTABLES = HelloWorld algorithm_lambda FourierTransform harmonic_oscillator lapack_basic lapack_matrix random openmp openmp_random static_example vector

# By default, all will be build by makefile
all: $(EXECUTABLES)

clean:
	rm -f -v $(EXECUTABLES)

HelloWorld: HelloWorld.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# nb:
# "$@" expands to taget name
# So, this is equivilant to:
# g++ -o HelloWorld HelloWorld.cpp -Wall -Wextra -Wpedantic -Wconversion -O3

algorithm_lambda: algorithm_lambda.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# This one requires GSL library
FourierTransform: FourierTransform.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -lgsl

harmonic_oscillator: harmonic_oscillator.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# This one requires GSL library
lambda: lambda.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# this uses LAPACK
lapack_basic: lapack_basic.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -llapack -lblas

# this uses LAPACK
lapack_matrix: lapack_matrix.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -llapack -lblas

random: random.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# this uses OPENMP
openmp: openmp.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -fopenmp

# this uses OPENMP
openmp_random: openmp_random.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -fopenmp

static_example: static_example.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

vector: vector.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

multi-file: multi-file-example/main.cpp multi-file-example/functions.cpp  multi-file-example/functions.hpp multi-file-example/other.cpp multi-file-example/other.hpp
	$(CXX) $(STD) -o $@ multi-file-example/main.cpp multi-file-example/functions.cpp multi-file-example/other.cpp $(WARN) $(OPT)