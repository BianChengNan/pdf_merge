#include "pdf_generator.h"

PDFGenerator::PDFGenerator() :
  reader(),
  writer(){
};

bool PDFGenerator::file_exists(std::string & path){
  if (FILE * file = fopen(path.c_str(), "r")) {
    fclose(file);
    return true;
  } else return false;
}

void PDFGenerator::generate(const std::string & target_file){
  if (writer.StartPDF(target_file.c_str(), ePDFVersion13) != EStatusCode::eSuccess)
    throw FailedToOpenPDFFile();

  for (std::string * file : files){
    if (writer.AppendPDFPagesFromPDF(file->c_str(), PDFPageRange()).first != eSuccess)
      throw FailedToOpenPDFFile();
  }

  if (writer.EndPDF() != EStatusCode::eSuccess)
    throw FailedToClosePDFFile();
}

void PDFGenerator::add_file(std::string & path, int position){
  if (!file_exists(path)) throw FileDoesNotExist();

  if (position == ADD_TO_END) {
    files.push_back(&path);
    return;
  }

  int true_position = position;
  if (position > files.size()) true_position = files.size();

  auto target_pos = files.begin();
  for (int i = 0; i < true_position; i++) target_pos++;

  files.insert(target_pos, &path);
}

const std::vector<std::string*> & PDFGenerator::get_files(){return files;}
