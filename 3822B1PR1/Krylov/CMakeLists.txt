cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME sparse_matrix)
project(${PROJECT_NAME})

set(PROJ_TESTS "test_${PROJECT_NAME}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" gtest)

add_subdirectory(samples)
