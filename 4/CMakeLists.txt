cmake_minimum_required(VERSION 3.22)
project(4 C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

add_executable(4 src/main.c src/Q2/Q2.cpp src/Q2/Q2.h src/Q3/Q3.c src/Q3/Q3.h src/Q2/Page.cpp src/Q2/Page.hpp src/Q2/PageReferenceString.cpp src/Q2/PageReferenceString.hpp src/Q2/AbstractAlgorithm.cpp src/Q2/AbstractAlgorithm.hpp src/Q2/LRUAlgorithm.cpp src/Q2/LRUAlgorithm.hpp src/Q2/FIFOAlgorithm.cpp src/Q2/FIFOAlgorithm.hpp src/Q3/SharedMemory.c src/Q3/SharedMemory.h src/Q3/CatalanNumber.c src/Q3/CatalanNumber.h)
