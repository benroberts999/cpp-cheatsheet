#include <fstream> // read/write to file
#include <iostream>
#include <string>

// try: ./01a-BasicInputOutput a b c d

int main(int argc, char *argv[]) {

  std::cout << "There were: " << argc << " command-line input options\n.";
  std::cout << "They were:\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << i << ") " << argv[i] << "\n";
  }
}
