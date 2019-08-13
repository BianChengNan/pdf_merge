#pragma once

#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Option {
  std::wstring name;
  std::wstring value;
};


class NoSuchOption: public std::exception {};


class ArgParser{
  private:
    std::vector<std::wstring> arguments;
    std::vector<Option> options;
    bool argument_is_option(const std::wstring & arg);
    Option parse_option(const std::wstring & option_string);
  public:
    ArgParser(const int argc, const wchar_t ** argv);
    const std::vector<Option> & get_options();
    const std::vector<std::wstring> & get_arguments();
    const std::wstring & get_option(const std::wstring & option_name);
};
