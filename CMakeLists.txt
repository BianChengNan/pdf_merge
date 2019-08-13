cmake_minimum_required(VERSION 3.14.3)

add_definitions(-DUNICODE -D_UNICODE)

project(pdf_merge)

#----------------------
#   GoogleTest
#----------------------
# Download and unpack googletest at configure time
configure_file(googletest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)



configure_file(pdfwriter.in pdf_writer-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pdf_writer-download )
if(result)
  message(FATAL_ERROR "CMake step for PDFWriter failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pdf_writer-download )
if(result)
  message(FATAL_ERROR "Build step for PDFWriter failed: ${result}")
endif()
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/pdf_writer-src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/pdf_writer-src EXCLUDE_FROM_ALL)


include_directories(${PROJECT_SOURCE_DIR}/pdf_merge/include/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(mergepdf ${PROJECT_SOURCE_DIR}/pdf_merge/src/main.cpp)
target_link_libraries(mergepdf PDFWriter)
target_sources(mergepdf
  PUBLIC
    ${PROJECT_SOURCE_DIR}/pdf_merge/src/arg_parser.cpp
    ${PROJECT_SOURCE_DIR}/pdf_merge/src/pdf_generator.cpp
)

enable_testing()
add_executable(mergepdf_test ${PROJECT_SOURCE_DIR}/pdf_merge/tests/main.cpp)
target_sources(mergepdf_test
  PUBLIC
    ${PROJECT_SOURCE_DIR}/pdf_merge/src/arg_parser.cpp
    ${PROJECT_SOURCE_DIR}/pdf_merge/src/pdf_generator.cpp
    ${PROJECT_SOURCE_DIR}/pdf_merge/tests/test_arg_parser.cpp
    ${PROJECT_SOURCE_DIR}/pdf_merge/tests/test_pdf_generator.cpp
)
target_link_libraries(mergepdf_test gtest_main)
target_link_libraries(mergepdf_test gmock_main)
target_link_libraries(mergepdf_test PDFWriter)
add_test(NAME mergepdf_test COMMAND mergepdf_test)
