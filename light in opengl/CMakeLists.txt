cmake_minimum_required(VERSION 3.31.3)
project(OpenGL)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

#tell linker where to find tthe libraries
link_directories(${CMAKE_SOURCE_DIR}/libs)

#add resource file
set(RESOURCE_FILE assets/icons/resources.rc)

#executable
add_executable(OpenGL 
src/main.cpp 
src/glad.c 
src/mine/mine.cpp 
src/mine/window.cpp 
src/mine/render.cpp 
src/mine/shader.cpp
src/mine/cube.cpp
include/mine/events/events.cpp
${RESOURCE_FILE})

if(MINGW)
   set(CMAKE_RC_COMPILER_INIT windres)
   enable_language(RC)
endif()

#link glfw and openGL
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL glfw3 OpenGL::GL)

