cmake_minimum_required(VERSION 3.10)

project(Light)
# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)


#tell linker where to find tthe libraries
link_directories(${CMAKE_SOURCE_DIR}/libs)
add_definitions(-DGLFW_BUILD_JOYSTICK=0)
add_executable(Light 
src/main.cpp 
src/glad.c
)

#link glfw and openGL
#find_package(FreeType REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(Light glfw freetype OpenGL::GL)
