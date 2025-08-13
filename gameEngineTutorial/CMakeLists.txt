#top level cmake

cmake_minimum_required(
    VERSION 3.31.3
)
project(roseProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)



add_subdirectory(sandbox)
add_subdirectory(rose)
#add sub_directory() tells opengl to go into rose/ and sandbox/ and build both