cmake_minimum_required(VERSION 3.20)
project(AmityEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Amity
    src/core/main.cpp
    src/core/Application.cpp
    src/core/Renderable.cpp
    src/core/Shader.cpp
)

# opengl packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

#glad
add_library(glad STATIC src/third_party/glad/glad.c)

# copy shaders
add_custom_command(
    TARGET Amity POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/src/shaders"
            "$<TARGET_FILE_DIR:Amity>/shaders"
    COMMENT "copy shaders to build dir"
)

target_include_directories(
    glad PUBLIC src/third_party/glad/include
)

target_link_libraries(Amity PRIVATE
    glfw
    OpenGL::GL
    glad
    glm::glm
)