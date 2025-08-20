cmake_minimum_required(VERSION 3.31.3)
project(revOp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Tell linker where to find the libraries
link_directories(${CMAKE_SOURCE_DIR}/libs)

# Add resource file
set(RESOURCE_FILE assets/icons/resources.rc)

# Executable
add_executable(revOp src/main.cpp src/glad.c ${RESOURCE_FILE})

if(MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    enable_language(RC)
endif()

if(WIN32)
    # link glfw and OpenGL (desktop)
    find_package(OpenGL REQUIRED)
    target_link_libraries(revOp glfw3 OpenGL::GL)
else()
    # link GLESv2 (Termux / Android)
    find_package(GLESv2 REQUIRED)
    target_link_libraries(revOp GLESv2)
endif()

