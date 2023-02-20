#include <fstream> // read/write to file
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// try: ./01a-BasicInputOutput a b c d

int main(int argc, char *argv[]) {

  std::cout << "There were: " << argc << " command-line input options\n.";
  std::cout << "They were:\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << i << ") " << argv[i] << "\n";
  }

  std::string in_word{""};
  int in_int{0};
  std::cout << "Please enter a word, then an integer:\n";
  std::cin >> in_word >> in_int;
  std::cout << "Thanks. The word you entered was: " << in_word
            << ", the integer you entered was" << in_int << "\n";

  // input/output to files using filestream:

  // Write that output to a file:
  std::string filename{"output_file.txt"};
  std::ofstream out_file(filename, std::ios::app);
  // the (optional) option, `std::ios::app` means we are opening this file in
  // "append" mode. We will write to the end of the file, without over-writing
  // anything else that was there already
  out_file << in_word << " " << in_int << '\n';

  // The file will 'close' itself, so this is usually optional
  out_file.close();
  //(We need to close it, because we're about to re-open it to read in)

  std::cout << "\nNow, read in from the file:\n";

  // Read back in what we read from the file:
  std::ifstream in_file(filename);
  if (!in_file.is_open()) {
    std::cout << "failed to open " << filename << '\n';
    return 1;
  }

  // read each line of file:
  std::string line;
  std::vector<std::string> words;
  std::vector<int> integers;
  while (std::getline(in_file, line)) {
    std::cout << "Line: " << line << "\n";
    // parse each word in each line
    std::stringstream ss(line);
    std::string tmp_word;
    int tmp_int;
    ss >> tmp_word >> tmp_int;
    words.push_back(tmp_word);
    integers.push_back(tmp_int);
  }

  std::cout << "The input file contained: " << words.size() << " words, and "
            << integers.size() << " integers. They were:\n";
  for (const std::string &word : words) {
    std::cout << word << ", ";
  }
  std::cout << "\n and: \n";
  for (int integer : integers) {
    std::cout << integer << ", ";
  }
  std::cout << "\n";
}
