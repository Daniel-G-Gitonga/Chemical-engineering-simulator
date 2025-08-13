#cmake for engine dll.. the engine is called rose...

project(rose)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

add_library(
    rose SHARED #dll named rose ... so all that we want in dll must be included here
    main/src.h  #engine exports.. macros defined...
    main/application.cpp
    main/entrypoint.h
    main/log.cpp
)
target_include_directories(
    rose PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes #external include files glad ect
)
target_compile_definitions(rose PRIVATE ROSE_BUILD_DLL) #set the macro as true to allow building it...

#tell linker where to find tthe libraries
link_directories(${CMAKE_SOURCE_DIR}/libs)

target_precompile_headers(
    rose
    PRIVATE
    "main/rose_pch.h"
)

add_custom_command(
    TARGET rose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:rose>
    $<TARGET_FILE_DIR:sandbox>
)

#link all external libraries
#find_package(OpenGL REQUIRED)
#target_link_libraries( rose PRIVATE glfw3 )
