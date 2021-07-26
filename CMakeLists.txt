cmake_minimum_required(VERSION 3.18)
project(
  pascal
  VERSION 0.1.0
  LANGUAGES CXX)
add_executable(pascal main.cpp freepascal.g.d_parser.cpp)
target_compile_features(pascal PRIVATE cxx_std_20)
target_link_libraries(pascal PRIVATE dparse)
