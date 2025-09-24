cmake_required(VERSION 3.10)

project(log)

add_executable(log src/main.cpp)

target_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(log )
