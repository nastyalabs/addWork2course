file(GLOB headers true "../include/*.h")
enable_language(CXX)

file(GLOB cpps true "*.cpp")
foreach(arg ${cpps})
    get_filename_component(OUTPUT_FILE_WE ${arg} NAME_WE)
    add_executable(${OUTPUT_FILE_WE} ${arg} ${headers})
    target_include_directories(${OUTPUT_FILE_WE} PUBLIC "../include/")
endforeach()
