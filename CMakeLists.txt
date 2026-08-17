cmake_minimum_required(VERSION 3.10)
project(ezc C)

set(CMAKE_C_STANDARD 99)
file(GLOB SOURCES "src/*.c")
add_executable(ezc ${SOURCES})

target_link_libraries(ezc gdi32 opengl32)