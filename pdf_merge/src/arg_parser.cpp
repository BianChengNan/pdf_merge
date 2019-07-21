#include "arg_parser.h"

ArgParser::ArgParser(const int argc, const char ** argv){
  for (int i = 0; i < argc; i++){
    std::string current_argument = argv[i];

    if (argument_is_option(current_argument)){
      options.push_back(
          parse_option(current_argument));
    } else {
      arguments.push_back(current_argument);
    }
  }
}

bool ArgParser::argument_is_option(const std::string & arg){
  return arg[0] == '-';
}

Option ArgParser::parse_option(
    const std::string & option_string){
  Option option;

  std::stringstream stream(option_string);
  std::vector<std::string> parts;
  std::string segment;
  while (std::getline(stream, segment, '=')){
    parts.push_back(segment);
  }
  option.name = parts[0].erase(0,1); // delete the dash;
  option.value=parts[1];

  return option;
}

const std::vector<Option> & ArgParser::get_options(){
  return options;
}

const std::vector<std::string> & ArgParser::get_arguments(){
  return arguments;
}

const std::string & ArgParser::get_option(const std::string &  option_name){
  for (Option & o : options)
    if (!o.name.compare(option_name)) return o.value;
  throw NoSuchOption();
}
