#include <iostream>
#include "arg_parser.h"

int main(int argc, const char ** argv) {
  ArgParser parser(argc, argv);
  std::cout << "Worked!" << std::endl;
  return 0;
}
