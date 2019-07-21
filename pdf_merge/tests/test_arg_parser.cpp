#include "arg_parser.h"
#include "gtest/gtest.h"

namespace {

  class ArgParserTest : public ::testing::Test {

    public:
      ArgParser * parser;

      ArgParserTest() {
        const char * args[] = {
          "arg1",
          "arg2",
          "-opt1=value1",
          "arg3",
          "-opt2=value2",
        };
        parser = new ArgParser(5, args);
      }
      ~ArgParserTest() {
        delete parser;
      }


  };

  TEST_F(ArgParserTest, ConstructedCorrectly) {
    auto options = parser->get_options();
    auto args = parser->get_arguments();

    ASSERT_EQ(3, args.size());
    ASSERT_EQ(2, options.size());
  }

  TEST_F(ArgParserTest, OptionsRetrievedCorrectly) {
    ASSERT_STREQ("value1", parser->get_option("opt1").c_str());
    ASSERT_STREQ("value2", parser->get_option("opt2").c_str());
  }

  TEST_F(ArgParserTest, ExceptionRaisedForNoOption) {
    ASSERT_THROW(parser->get_option("opt3"), NoSuchOption);
  }
}  // namespace
