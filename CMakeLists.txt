cmake_minimum_required(VERSION 3.16)
project(1CTextFinder)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(src)

include_directories(include)
link_directories(${1CTextFinder_SOURCE_DIR}/lib)

add_executable(1CTextFinder main.cpp)
target_link_libraries(1CTextFinder dep_lib)