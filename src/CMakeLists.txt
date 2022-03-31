cmake_minimum_required(VERSION 3.16)

project(Dependencies)

FILE(GLOB Libs "${1CTextFinder_SOURCE_DIR}/include/*.h")

add_library(
         dep_lib SHARED parser.cpp ${Libs}
)