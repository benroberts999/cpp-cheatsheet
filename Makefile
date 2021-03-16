################################################################################
# This is a basic Makefile example.
# You can do much more with make - but this is a good start
# It makes compilation much easier and faster once you have larger projects
################################################################################

## Which compiler: (g++, clang++) [no spaces]
## Depending on your operating system, you may need to specify exactly where it is, or which version (e.g., CXX=g++-9)
CXX=g++
# CXX=clang++

# Can use this if you want the source files and built pobject files in seperate directories
SD=./
BD=./

## c++ standard.
# blank = default for whichever compiler you have (usually c++14)
# other options: -std=c++11, -std=c++14, -std=c++17, -std=c++20
# Each new version of c++ add some nice features, but require newer compilers
# They are all backwards compatible - code from 30 years ago will still compile
CXXSTD=-std=c++11

################################################################################
## Build config + options:
#Warnings:
WARN=-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Weffc++ -Wsign-conversion

# Note: I use lots of warnings; you don't have to - but I consider the first 3 to be mandatory (so as not to form bad coding habits)

# Optimisation level
#OPT=-O3

################################################################################
# Linking + Compiling:
# [CXXFLAGS are passed at compilation, LIBS at linking]

CXXFLAGS= $(CXXSTD) $(OPT) $(WARN) -I$(SD)
LIBS=

# -fopenmp allows openmp parallelisation - not needed if not used

# For example, to use GSL libraries, write:
#LIBS=-lgsl -lgslcblas

# Command to compile objects and link them
COMP=$(CXX) -c -o $@ $< $(CXXFLAGS)
LINK=$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

# (The fancy notation here is Makefile voodoo to automatically name the object files the same as the cpp files)

################################################################################
# Compile all cpp files into "object" files
$(BD)/%.o: $(SD)/%.cpp $(SD)/%.hpp $(SD)/templates.hpp
	$(COMP)

# Means: for every *.cpp file in the SD/ directory, compile to a *.o in the BD/ directory
# NB: there are better automated ways of listing dependencies..

################################################################################
# Link the compiled files + build all final programs
# will produce an executable called 'main'
main: $(BD)/main.o $(BD)/functions.o $(BD)/otherFunctions.o $(BD)/VectorArraySTL.o $(BD)/classExample.o $(BD)/random.o
	$(LINK)

# Note: there are fancy ways to automatically determine the dependencies - but for simple projects it doesn't matter

# Default make rule:
all: main

clean:
	rm -f main $(BD)/main.o $(BD)/functions.o $(BD)/otherFunctions.o $(BD)/VectorArraySTL.o $(BD)/classExample.o $(BD)/random.o
