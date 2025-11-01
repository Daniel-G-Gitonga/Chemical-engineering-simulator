cmake_minimum_required(VERSION 3.14)
project(ChemEng_stuff CXX C)
#set(LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_subdirectory(core)
add_subdirectory(sandBox)
