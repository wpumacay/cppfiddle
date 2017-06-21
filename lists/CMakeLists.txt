
cmake_minimum_required(VERSION 2.8.9)
project (OrderedLists)

include_directories(listVariations)

file( GLOB SOURCES "./*.cpp" )

set(CMAKE_CXX_STANDARD 11)

add_executable(testingApp testingApp.cpp)