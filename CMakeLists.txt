cmake_minimum_required(VERSION 3.0.0)
project(parametric_shapes VERSION 0.1.0)


add_executable(parametric_shapes main.cpp)

target_link_libraries(parametric_shapes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/shape_lib/lib/libshapes_lib.so)

target_include_directories(parametric_shapes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/shape_lib/include)
