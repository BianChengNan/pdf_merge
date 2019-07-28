#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include "arg_parser.h"
#include "pdf_generator.h"

std::shared_ptr<ArgParser> parse_args(const int, const char **);
void ensure_minimum_arguments(const std::shared_ptr<ArgParser>);
void ensure_output_file_provided(const std::shared_ptr<ArgParser>);

int main(int argc, const char ** argv) {
  std::shared_ptr<ArgParser> parser;
  try{
    parser = parse_args(argc, argv);
  } catch (const int&) {
    return -1;
  }

  PDFGenerator generator;
  for (const std::string & file: parser->get_arguments()) {
    generator.add_file(const_cast<std::string&>(file));
  }

  generator.generate(parser->get_option("output"));

  return 0;
}


std::shared_ptr<ArgParser> parse_args(const int argc, const char ** argv) {
  // skip the first argument as its just the application call
  std::shared_ptr<ArgParser> parser(new ArgParser(argc-1, argv+1));

  ensure_minimum_arguments(parser);
  ensure_output_file_provided(parser);

  return parser;
}

void ensure_minimum_arguments(const std::shared_ptr<ArgParser> parser){
  if (parser->get_arguments().size() < 2) {
    std::cout << "You must provide paths to at least 2 pdf files to merge together" << std::endl;
    throw -1;
  }
}

void ensure_output_file_provided(const std::shared_ptr<ArgParser> parser){
  try {
    parser->get_option("output");
  } catch (NoSuchOption&){
    std::cout << "You must provide a -output=[filepath] argument for the output file" << std::endl;
    throw -1;
  }
}
