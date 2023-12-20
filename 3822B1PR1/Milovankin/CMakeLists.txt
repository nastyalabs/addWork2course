cmake_minimum_required(VERSION 3.10)
project(Matrix-Types)

# Add header files
include_directories(inc)

# Add source files
set(SOURCES
    smp/crsmatrix_sample.cpp
    smp/flatmatrix_sample.cpp
)

# Create an executable for each source file
foreach(SOURCE ${SOURCES})
    # Get the filename without the extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    # Add an executable with the name of the file (without extension)
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
    # Link the executable with headers
    target_include_directories(${EXECUTABLE_NAME} PRIVATE inc)
endforeach()