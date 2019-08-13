#include <windows.h>
#include "pdf_generator.h"

std::string UnicodeToUtf8(const std::wstring& unicode)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
	std::string result; result.resize(len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, (char*)result.c_str(), len, NULL, NULL);
	return result;
}

PDFGenerator::PDFGenerator() :
  reader(),
  writer(){
};

bool PDFGenerator::file_exists(const std::wstring & path)
{
	if (FILE * file = _wfopen(path.c_str(), L"r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

void PDFGenerator::generate(const std::wstring & target_file){
	if (writer.StartPDF(UnicodeToUtf8(target_file), ePDFVersion13) != EStatusCode::eSuccess)
		throw FailedToOpenPDFFile();

	for (const auto& file : files){
		if (writer.AppendPDFPagesFromPDF(UnicodeToUtf8(file), PDFPageRange()).first != eSuccess)
			throw FailedToOpenPDFFile();
	}

	if (writer.EndPDF() != EStatusCode::eSuccess)
		throw FailedToClosePDFFile();
}

void PDFGenerator::add_file(const std::wstring& path, int position)
{
	if (!file_exists(path))
	{
		throw FileDoesNotExist();
	}

	if (position == ADD_TO_END)
	{
		files.push_back(path);
		return;
	}

	int true_position = position;
	if (position > files.size())
	{
		true_position = files.size();
	}

	auto target_pos = files.begin();
	for (int i = 0; i < true_position; i++)
	{
		target_pos++;
	}

	files.insert(target_pos, path);
}

const std::vector<std::wstring> & PDFGenerator::get_files(){ return files; }
