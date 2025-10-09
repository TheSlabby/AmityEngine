cmake_minimum_required(VERSION 3.20)
project(AmityEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Define the executable and its source files ---
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

# ===================================================================
#                  FIND LIBRARIES (PORTABLE METHOD)
# ===================================================================

# Use standard CMake modules for these as they don't use pkg-config
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# Check if pkg-config is available on the system
find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
    message(STATUS "Using pkg-config to find libraries.")
    pkg_check_modules(GLFW3 REQUIRED glfw3)
    pkg_check_modules(ASSIMP REQUIRED assimp)
    pkg_check_modules(OPENAL REQUIRED openal)
    pkg_check_modules(SNDFILE REQUIRED sndfile)
    pkg_check_modules(STB REQUIRED stb)
else()
    message(STATUS "pkg-config not found. Using standard find_package.")
    find_package(glfw3 REQUIRED)
    find_package(assimp REQUIRED)
    find_package(OpenAL REQUIRED)
    find_package(SndFile REQUIRED)
    find_package(Stb REQUIRED)
endif()

# --- Include all necessary header directories ---
target_include_directories(Amity PRIVATE
    # These variables work for both pkg-config and find_package!
    ${GLFW3_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIRS}
    ${SNDFILE_INCLUDE_DIRS}
    ${STB_INCLUDE_DIRS}
)


# --- Define local targets (like glad) ---
add_library(glad STATIC src/third_party/glad/glad.c)
target_include_directories(glad PUBLIC src/third_party/glad/include)


# --- Add post-build commands ---
add_custom_command(
    TARGET Amity POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/src/shaders"
            "$<TARGET_FILE_DIR:Amity>/shaders"
    COMMENT "copy shaders to build dir"
)

# --- Link all libraries at the end ---
target_link_libraries(Amity PRIVATE
    # CMake targets from find_package
    OpenGL::GL
    glm::glm

    # Library paths from pkg-config OR find_package
    ${GLFW3_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${OPENAL_LIBRARIES}
    ${SNDFILE_LIBRARIES}

    # Our own static library
    glad
)