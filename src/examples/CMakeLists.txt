cmake_minimum_required(VERSION 3.0)

project(Examples)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${1CTextFinder_SOURCE_DIR}/examples)

include_directories(${1CTextFinder_SOURCE_DIR}/include)
link_directories(${1CTextFinder_SOURCE_DIR}/lib)

add_executable(CountEntries CountEntries.cpp)
add_executable(FirstOccurrence FirstOccurrence.cpp)
add_executable(OccurrenceContext OccurrenceContext.cpp)
add_executable(AllInOne AllInOne.cpp)

target_link_libraries(CountEntries dep_lib)
target_link_libraries(FirstOccurrence dep_lib)
target_link_libraries(OccurrenceContext dep_lib)
target_link_libraries(AllInOne dep_lib)