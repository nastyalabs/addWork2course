#cmake_minimum_required(VERSION 3.13)
#include(FetchContent)

#FetchContent_Declare(
#  googletest
#  GIT_REPOSITORY https://github.com/google/googletest.git
#  GIT_TAG        release-1.11.0
#)
#FetchContent_GetProperties(googletest)

#if (NOT googletest_POPULATED)
#  FetchContent_Populate(googletest)
#  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
#endif()
#FetchContent_MakeAvailable(googletest)
#add_library(GTest::GTest INTERFACE IMPORTED)

file(GLOB anotherheaders true "../include/*.h")
file(GLOB test_cpps true "*.cpp")
file(GLOB test_hdrs true "*.h")

add_library(gtest STATIC "../gtest/gtest-all.cc" "../gtest/gtest.h")

set(TEST_NAME test_${PROJECT_NAME})
add_executable(${TEST_NAME} ${test_cpps} ${test_hdrs} ${anotherheaders})

target_link_libraries(${TEST_NAME} PUBLIC gtest)
target_include_directories(${TEST_NAME} PUBLIC "../include" "../gtest")

#add_test(${TEST_NAME})
