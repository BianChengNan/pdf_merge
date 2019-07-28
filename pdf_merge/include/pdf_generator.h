#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <memory>
#include "PDFWriter/PDFParser.h"
#include "PDFWriter/PDFWriter.h"

class FileDoesNotExist : public std::exception {};

class PDFGenerator{
  private:
    std::vector<std::string*> files;
    std::string * target_file;
    PDFParser reader;
    PDFWriter writer;

    virtual bool file_exists(std::string & path);
  public:
    static const int ADD_TO_END = -1;

    PDFGenerator();

    void generate();
    void add_file(std::string & path, int position=ADD_TO_END);
    const std::vector<std::string*> & get_files();
};
