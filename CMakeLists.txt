cmake_minimum_required(VERSION 3.20)
project(AmityEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Amity
    src/app/main.cpp
    src/app/TestGame.cpp
    src/core/Application.cpp
    src/core/Shader.cpp
    src/core/ModelRenderable.cpp
    src/core/TerrainRenderable.cpp
    src/core/Scene.cpp
    src/core/Camera.cpp
    src/core/Sound.cpp
)

include_directories(src/core)

# opengl packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_package(Stb REQUIRED)
find_package(OpenAL REQUIRED)
find_package(SndFile REQUIRED)

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
    assimp::assimp
    OpenAL::OpenAL
    SndFile::sndfile
)