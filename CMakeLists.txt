cmake_minimum_required(VERSION 3.20)
project(AmityEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Amity
    src/core/main.cpp
)

# opengl packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(Amity PRIVATE
    glfw
    OpenGL::GL
)