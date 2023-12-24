cmake_minimum_required(VERSION 3.10)
project(Matrix-Types)

include_directories(inc)

set(SOURCES
    smp/crsmatrix_sample.cpp
    smp/flatmatrix_sample.cpp
)

foreach(SOURCE ${SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE inc)
endforeach()