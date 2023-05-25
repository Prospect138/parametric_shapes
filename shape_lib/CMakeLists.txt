cmake_minimum_required(VERSION 3.0.0)
project(shapes_lib VERSION 0.1.0)

add_library(shapes_lib SHARED 
include/shape.cpp
include/shape.h)

target_include_directories(shapes_lib PUBLIC include)

set_target_properties(shapes_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)