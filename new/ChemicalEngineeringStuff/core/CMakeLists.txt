cmake_minimum_required(VERSION 3.14)

project(core CXX)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libs)

add_library(
    core SHARED
    src/win.cpp
    src/app.cpp
    src/render.cpp
    
    
)

target_compile_definitions(core PRIVATE EXPORT_ROSES)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_precompile_headers(
        core
        PUBLIC  
        src/pch.h
        )

find_package(OpenGL REQUIRED)

set_source_files_properties(src/src/glad.c PROPERTIES LANGUAGE C)

add_library(
 glad STATIC
 src/src/glad.c
)

target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(
    core
    PUBLIC
    glad
    glfw3dll.lib
    OpenGL::GL
    opengl32
    
)

add_custom_command(
    TARGET core 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../build/core/libcore.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/../build/sandBox/"
    COMMENT "COPYING CORE DLL"
    )

