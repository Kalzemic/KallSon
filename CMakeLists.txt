cmake_minimum_required(VERSION 3.0.0)
project (Kallson Version 0.0.1 LANGUAGES c CXX)

include(CTest)
enable_testing()

add_executable(KallSon test.cpp)

set_property(TARGET MyCMakeproject PROPERTY CXX_STANDARD 17)