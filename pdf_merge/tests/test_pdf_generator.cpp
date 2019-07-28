#include "pdf_generator.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;

namespace {

  class PDFGeneratorMock: public PDFGenerator {
    public:
      MOCK_METHOD(bool, file_exists, (std::string &path), ());
  };

  class PDFGeneratorTest : public ::testing::Test {

    public:
      PDFGeneratorMock * generator;
      std::string * file_1;
      std::string * file_2;

      PDFGeneratorTest() {
        file_1 = new std::string("file1.pdf");
        file_2 = new std::string("file2.pdf");
        generator = new PDFGeneratorMock();

        ON_CALL(*generator, file_exists(*file_1))
          .WillByDefault(Return(true));
        ON_CALL(*generator, file_exists(*file_2))
          .WillByDefault(Return(true));
      }
      ~PDFGeneratorTest() {
        delete generator;
        delete file_1;
        delete file_2;
      }


  };

  TEST_F(PDFGeneratorTest, ConstructedCorrectly) {
    ASSERT_EQ(0, generator->get_files().size());
  }

  TEST_F(PDFGeneratorTest, AppendsFileToEndByDefault) {
    generator->add_file(*file_1);
    generator->add_file(*file_2);

    ASSERT_EQ(2, generator->get_files().size());
    ASSERT_STREQ(file_1->c_str(), generator->get_files()[0]->c_str());
    ASSERT_STREQ(file_2->c_str(), generator->get_files()[1]->c_str());
  }

  TEST_F(PDFGeneratorTest, AppendsFileAtCorrectIndex) {
    generator->add_file(*file_1);
    generator->add_file(*file_2, 0);

    ASSERT_EQ(2, generator->get_files().size());
    ASSERT_STREQ(file_2->c_str(), generator->get_files()[0]->c_str());
    ASSERT_STREQ(file_1->c_str(), generator->get_files()[1]->c_str());
  }

  TEST_F(PDFGeneratorTest, AppendsFileAtEndForTooHighIndex) {
    generator->add_file(*file_1);
    generator->add_file(*file_2, 3);

    ASSERT_EQ(2, generator->get_files().size());
    ASSERT_STREQ(file_1->c_str(), generator->get_files()[0]->c_str());
    ASSERT_STREQ(file_2->c_str(), generator->get_files()[1]->c_str());
  }

  TEST_F(PDFGeneratorTest, ExceptionRaisedForNoFile) {
    std::string file = "blah blah blah";
    ON_CALL(*generator, file_exists(file))
      .WillByDefault(Return(false));

    ASSERT_THROW(generator->add_file(file), FileDoesNotExist);
  }
}
