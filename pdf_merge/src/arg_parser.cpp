#include "arg_parser.h"

ArgParser::ArgParser(const int argc, const wchar_t ** argv){
  for (int i = 0; i < argc; i++){
    std::wstring current_argument = argv[i];

    if (argument_is_option(current_argument)){
      options.push_back(
          parse_option(current_argument));
    } else {
      arguments.push_back(current_argument);
    }
  }
}

bool ArgParser::argument_is_option(const std::wstring & arg){
  return arg[0] == L'-';
}

Option ArgParser::parse_option(
    const std::wstring & option_string){
  Option option;

  std::wstringstream stream(option_string);
  std::vector<std::wstring> parts;
  std::wstring segment;
  while (std::getline(stream, segment, L'=')){
    parts.push_back(segment);
  }
  option.name = parts[0].erase(0,1); // delete the dash;
  option.value=parts[1];

  return option;
}

const std::vector<Option> & ArgParser::get_options(){
  return options;
}

const std::vector<std::wstring> & ArgParser::get_arguments(){
  return arguments;
}

const std::wstring & ArgParser::get_option(const std::wstring &  option_name){
  for (Option & o : options)
    if (!o.name.compare(option_name)) return o.value;
  throw NoSuchOption();
}
