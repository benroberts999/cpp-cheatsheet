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

01-Basic: 01-Basic.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# nb:
# "$@" expands to the taget name
# So, this is equivilant to:
# g++ -std=c++17 -o 01-Basic 01-Basic.cpp -Wall -Wextra -Wpedantic -Wconversion -O3

01a-BasicInputOutput: 01a-BasicInputOutput.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

02-functions-basic: 02-functions-basic.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

02a-multi-file-example: 02a-multi-file-example.cpp multi-file-example/functions.cpp multi-file-example/functions.hpp  multi-file-example/other.cpp multi-file-example/other.hpp
	$(CXX) $(STD) -o $@ $@.cpp multi-file-example/functions.cpp multi-file-example/other.cpp $(WARN) $(OPT)

03-ClassesStructs: 03-ClassesStructs.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

04-Namespaces: 04-Namespaces.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

05-templates: 05-templates.cpp 05-templates.hpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

06-VectorArray: 06-VectorArray.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

07-algorithm_lambda: 07-algorithm_lambda.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

08-random: 08-random.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# this uses OPENMP, -fopenmp
09-openmp: 09-openmp.cpp
	$(CXX) $(STD) -fopenmp -o $@ $@.cpp $(WARN) $(OPT)

10-openmp_random: 10-openmp_random.cpp
	$(CXX) $(STD) -fopenmp  -o $@ $@.cpp $(WARN) $(OPT)

11-static_example: 11-static_example.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# More advanced examples:

#This one ises the GSL library (-lgsl)
# It must be installed: sudo apt-get install libgsl-dev
FourierTransform: FourierTransform.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -lgsl

harmonic_oscillator: harmonic_oscillator.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT)

# These two require LAPACK and BLAS libraries:
lapack_basic: lapack_basic.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -llapack -lblas

lapack_matrix: lapack_matrix.cpp
	$(CXX) $(STD) -o $@ $@.cpp $(WARN) $(OPT) -llapack -lblas