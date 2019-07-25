#pragma once

#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Option {
  std::string name;
  std::string value;
};


class NoSuchOption: public std::exception {

};


class ArgParser{
  private:
    std::vector<std::string> arguments;
    std::vector<Option> options;
    bool argument_is_option(const std::string & arg);
    Option parse_option(const std::string & option_string);
  public:
    ArgParser(const int argc, const char ** argv);
    const std::vector<Option> & get_options();
    const std::vector<std::string> & get_arguments();
    const std::string & get_option(const std::string & option_name);
};
