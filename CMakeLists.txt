cmake_minimum_required(VERSION 3.19)
project(cs_452_lab_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(cs_452_lab_02 main.cpp Queue.cpp Queue.h process.cpp process.h rt.cpp rt.h mfqs.h mfqs.cpp)