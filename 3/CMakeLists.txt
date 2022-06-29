cmake_minimum_required(VERSION 3.22)
project(3 CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(3 src/main.cpp src/entities/World.cpp src/entities/World.hpp src/entities/TeachingAssistant.cpp src/entities/TeachingAssistant.hpp src/entities/Student.cpp src/entities/Student.hpp src/utils/ThreadSafeQueue.cpp src/utils/ThreadSafeQueue.hpp src/utils/SynchronizedOutputStream.cpp src/utils/SynchronizedOutputStream.hpp)
