cmake_minimum_required(VERSION 3.10)

project(concurrency)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS -pthread)

add_subdirectory(${PROJECT_SOURCE_DIR}/basic)