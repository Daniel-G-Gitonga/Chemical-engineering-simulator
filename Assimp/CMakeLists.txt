cmake_minimum_required(VERSION 3.14)

project(Assimp_)

include_directories(Assimp_ ${CMAKE_SOURCE_DIR}/includes)

add_executable(Assimp_ Assets/icon/icon.rc main/app.cpp main/main.cpp main/model.cpp  main/glad.c)

target_link_directories(Assimp_ PUBLIC ${CMAKE_SOURCE_DIR}/lib)

find_package(OpenGL REQUIRED)
target_link_libraries(Assimp_ PUBLIC glfw3dll.lib libassimpd.dll.a OpenGL::GL)

add_custom_command(
    
    TARGET Assimp_
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/build/Assimp_.exe"
    "${CMAKE_SOURCE_DIR}/executable/"
)
