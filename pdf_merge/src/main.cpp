#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include "arg_parser.h"

std::shared_ptr<ArgParser> parse_args(const int, const char **);

int main(int argc, const char ** argv) {
  std::shared_ptr<ArgParser> parser;
  try{
    parser = parse_args(argc, argv);
  } catch (const int&) {
    return -1;
  }

  return 0;
}


std::shared_ptr<ArgParser> parse_args(const int argc, const char ** argv) {
  // skip the first argument as its just the application call
  std::shared_ptr<ArgParser> parser(new ArgParser(argc-1, argv+1));

  std::vector<std::string> pdf_files = parser->get_arguments();
  if (pdf_files.size() < 2) {
    std::cout << "You must provide paths to at least 2 pdf files to merge together" << std::endl;
    throw -1;
  }

  std::string output;
  try {
    output = parser->get_option("output");
  } catch (NoSuchOption&){
    std::cout << "You must provide a -output=[filepath] argument for the output file" << std::endl;
    throw -1;
  }

  return parser;
}
