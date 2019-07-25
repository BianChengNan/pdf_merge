#include <iostream>
#include <vector>
#include <string>
#include "arg_parser.h"

int main(int argc, const char ** argv) {
  ArgParser parser(argc, argv);
  std::vector<std::string> pdf_files = parser.get_arguments();

  std::string output;
  try {
    output = parser.get_option("output");
  } catch (NoSuchOption e){
    std::cout << "You must provide a -output=[filepath] argument for the output file" << std::endl;
  }

  return 0;
}
