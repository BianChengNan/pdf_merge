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


class PDFGenerator{
  private:
    std::vector<std::string> files;
  public:
    void generate(const std::string & target_file);
};
