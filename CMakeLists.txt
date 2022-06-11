cmake_minimum_required(VERSION 3.20)
project(ex3)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(ex3 main.cpp BoundedQueue.cpp BoundedQueue.h UnboundedQueue.cpp UnboundedQueue.h Semaphore.cpp Semaphore.h)
