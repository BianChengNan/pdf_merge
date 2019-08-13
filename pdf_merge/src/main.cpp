#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <memory>
#include "arg_parser.h"
#include "pdf_generator.h"

std::shared_ptr<ArgParser> parse_args(const int, const wchar_t **);
void ensure_minimum_arguments(const std::shared_ptr<ArgParser>);
void ensure_output_file_provided(const std::shared_ptr<ArgParser>);

int wmain(int argc, const wchar_t ** argv)
{
  std::shared_ptr<ArgParser> parser;
  try
  {
    parser = parse_args(argc, argv);
  }
  catch (const int&)
  {
    return -1;
  }

  PDFGenerator generator;
  for (const auto& file: parser->get_arguments()) {
    generator.add_file(file);
  }

  generator.generate(parser->get_option(L"output"));

  return 0;
}


std::shared_ptr<ArgParser> parse_args(const int argc, const wchar_t ** argv) {
  // skip the first argument as its just the application call
  std::shared_ptr<ArgParser> parser(new ArgParser(argc-1, argv+1));

  ensure_minimum_arguments(parser);
  ensure_output_file_provided(parser);

  return parser;
}

void ensure_minimum_arguments(const std::shared_ptr<ArgParser> parser){
  // allow only one pdf file, this can be treated as rename operation
  if (parser->get_arguments().size() < 1) 
  {
    std::cout << "You must provide paths to at least one pdf files to merge together" << std::endl;
    throw -1;
  }
}

void ensure_output_file_provided(const std::shared_ptr<ArgParser> parser){
  try {
    parser->get_option(L"output");
  } catch (NoSuchOption&){
    std::cout << "You must provide a -output=[filepath] argument for the output file" << std::endl;
    throw -1;
  }
}
