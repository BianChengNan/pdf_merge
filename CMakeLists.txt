cmake_minimum_required(VERSION 3.14.3)

project(pdf_merge)

include_directories(${PROJECT_SOURCE_DIR}/pdf_merge/include/)
add_executable(app ${PROJECT_SOURCE_DIR}/pdf_merge/src/main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
