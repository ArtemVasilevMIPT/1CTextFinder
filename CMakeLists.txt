cmake_minimum_required(VERSION 3.16)
project(1CTextFinder)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${1CTextFinder_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)
add_subdirectory(src/examples)
include_directories(include)
link_directories(${1CTextFinder_SOURCE_DIR}/lib)

add_executable(1CTextFinder main.cpp)
target_link_libraries(1CTextFinder dep_lib)