#cmake for game...

project(sandbox)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)


add_executable(
    sandbox main/main.cpp
)
target_link_libraries(
    sandbox PRIVATE rose
)
target_include_directories(
    sandbox PRIVATE ../rose
)


if(MINGW)
    target_link_options(sandbox PRIVATE -mconsole)
endif()

file(GLOB DLL_FILES "${CMAKE_SOURCE_DIR}/bin/*.dll")
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILES}
            $<TARGET_FILE_DIR:sandbox>
)


#find_package(OpenGL REQUIRED)
#target_link_libraries(sandbox PRIVATE rose)

