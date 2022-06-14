cmake_minimum_required(VERSION 3.22)
project(2 C)

set(CMAKE_C_STANDARD 23)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(2 src/main.c src/Q1.c src/Q2.c)
target_link_libraries(2 ${CMAKE_THREAD_LIBS_INIT})

