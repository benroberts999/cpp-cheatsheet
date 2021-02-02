# c++ cheat sheet

This is a very basic set of examples for using c++.
Start at "main.cpp" - everything else is called from there.

## Get Compiler

### Linux (ubuntu)
  * Two most common free compilers (probably already installed)
  * sudo apt install g++
  * sudo apt install clang++

### MacOS
  * Install homebrew
  * brew install g++
  * NOTE: For some reason, on mac, 'g++' is actually an alias for clang++. So, if you want to actually use g++ and not clang++, you need to point to the specific (e.g., g++ => g++-9)

### Windows
  * With windows 10, the easiest way is to install 'windows subsystem for linux'
  * Using the windows app store, install ubuntu
  * You will get a linux bash terminal that runs natively inside windows (not a virtual machine)
  * Your windows filesystem can be accessed from inside bash at /mnt/c/ (be *very* careful - there is no recycle bin, 'rm' is for life)
    * You cannot access the ubuntu filesystem from windows except through the terminal
  * Then, everything goes as it did for ubuntu


## Compile

  * Two ways to compile.
  * Use Makefile. Once make is installed (sudo apt install make)
    * Simply run 'make' from command line
  * Alternatively: use old style:
    * g++ -std=c++14 -O3 main.cpp functions.cpp otherFunctions.cpp classExample.cpp VectorArraySTL.cpp -o main
    * clang++ -std=c++14 -O3 main.cpp functions.cpp otherFunctions.cpp classExample.cpp VectorArraySTL.cpp -o main
  * Then: run the executable: ./main

## Online resources:

 * https://www.cplusplus.com/
    * Good, lots of examples, beginner friendly
 * https://en.cppreference.com/
   * The standard resource, extremely thorough and detailed. Not very beginner-friendly however (reads like a maths textbook)
