cmake_minimum_required(VERSION 3.13)
project(forwork)

set(CMAKE_CXX_STANDARD 14)

add_executable(forwork blockfinder.cpp blockfinder_main.cpp classes.cpp ncs.cpp scheme.cpp PatternCodes.h PatternsCodes.cpp)