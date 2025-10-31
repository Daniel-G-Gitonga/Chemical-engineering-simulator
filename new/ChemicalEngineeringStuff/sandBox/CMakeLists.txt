cmake_minimum_required(VERSION 3.14)
project(sandBox CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../core/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../core/includes)

add_executable(sandBox sandBox.cpp)
target_link_libraries(sandBox PRIVATE core )
