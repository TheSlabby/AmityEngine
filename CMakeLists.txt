cmake_minimum_required(VERSION 3.20)

# Options that select vcpkg manifest features must be declared before project(),
# because vcpkg installs dependencies during project()
option(AMITY_ENABLE_LUA "Enable LuaScriptService" OFF)
option(AMITY_BUILD_TESTS "Build unit tests" ON)
if(AMITY_BUILD_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES tests)
endif()
if(AMITY_ENABLE_LUA)
    list(APPEND VCPKG_MANIFEST_FEATURES lua)
endif()

project(AmityEngine LANGUAGES CXX C)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(AMITY_BUILD_DEMOS "Build demo games (Amity test game, PanTiltShowcase, StormySails)" ON)
option(AMITY_BUILD_PRIVATE_GAMES "Build games in src/games/PrivateGames if present" ON)

# Enable parallel compilation for MSVC to dramatically speed up Windows builds
if(MSVC)
    add_compile_options(/MP)
endif()

# Find Package Dependencies (needed by core engine)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenAL REQUIRED)
find_package(LibSndFile REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Glad OpenGL Loader Library
add_library(glad STATIC src/third_party/glad/glad.c)
target_include_directories(glad PUBLIC src/third_party/glad/include)

# Lua Dependency (from vcpkg "lua" feature)
if(AMITY_ENABLE_LUA)
    find_package(Lua REQUIRED)
endif()

# Core Engine Static Library
add_library(AmityCore STATIC
    src/core/Application.cpp
    src/core/Log.cpp
    src/core/Shader.cpp
    src/core/ModelRenderable.cpp
    src/core/TerrainRenderable.cpp
    src/core/Scene.cpp
    src/core/Entity.cpp
    src/core/Sound.cpp
    src/core/FontManager.cpp
    src/core/UIRenderer.cpp
    src/core/user_input/UserInputService.cpp
    src/core/WaterRenderable.cpp
)


# Core Include Directories
target_include_directories(AmityCore PUBLIC src/core)
target_include_directories(AmityCore PUBLIC ${PROJECT_SOURCE_DIR}/src/third_party/stb)

# Core Link Libraries (Inherited transitively by downstream targets)
target_link_libraries(AmityCore PUBLIC
    glfw
    OpenGL::GL
    glad
    glm::glm
    assimp::assimp
    spdlog::spdlog
    ${LIBSNDFILE_LIBRARIES}
)

# OpenAL Linking logic (Modern vs Legacy fallback)
if(TARGET OpenAL::OpenAL)
    target_link_libraries(AmityCore PUBLIC OpenAL::OpenAL)
else()
    target_include_directories(AmityCore PUBLIC ${OPENAL_INCLUDE_DIR})
    target_link_libraries(AmityCore PUBLIC ${OPENAL_LIBRARY})
endif()

if(AMITY_ENABLE_LUA)
    target_sources(AmityCore PRIVATE src/core/scripting/LuaScriptService.cpp)
    target_include_directories(AmityCore PUBLIC ${LUA_INCLUDE_DIR})
    target_link_libraries(AmityCore PUBLIC ${LUA_LIBRARIES})
    target_compile_definitions(AmityCore PUBLIC AMITY_HAS_LUA=1)
endif()

if(AMITY_BUILD_DEMOS)

# Main Game Executable Target
add_executable(Amity
    src/app/main.cpp
    src/app/TestGame.cpp
)
target_link_libraries(Amity PRIVATE AmityCore)

# Post-Build Custom Command to copy shaders and scripts next to the executable
add_custom_command(
    TARGET Amity POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
            "$<TARGET_FILE_DIR:Amity>/shaders"
    COMMENT "copy shaders and scripts to build dir"
)



if(AMITY_ENABLE_LUA)
    add_custom_command(
        TARGET Amity POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_SOURCE_DIR}/src/app/script.lua"
                "$<TARGET_FILE_DIR:Amity>/script.lua"
        COMMENT "copy lua script to build dir"
    )
endif()


# Pan/Tilt Camera Showcase Target (PanTiltShowcase)
add_executable(PanTiltShowcase
    src/games/PanTiltShowcase/main.cpp
    src/games/PanTiltShowcase/PanTiltShowcaseGame.cpp
)
target_link_libraries(PanTiltShowcase PRIVATE AmityCore)
target_include_directories(PanTiltShowcase PRIVATE src/games/PanTiltShowcase)

# Post-Build Custom Command to copy shaders next to the PanTiltShowcase executable
add_custom_command(
    TARGET PanTiltShowcase POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
            "$<TARGET_FILE_DIR:PanTiltShowcase>/shaders"
    COMMENT "copy shaders to PanTiltShowcase build dir"
)

# Stormy Sails Sailing Game target (StormySails)
add_executable(StormySails
    src/games/StormySails/main.cpp
    src/games/StormySails/StormySailsGame.cpp
)
target_link_libraries(StormySails PRIVATE AmityCore)
target_include_directories(StormySails PRIVATE src/games/StormySails)
target_include_directories(StormySails PRIVATE src/third_party/stb)

# Post-Build Custom Command to copy shaders next to the StormySails executable
add_custom_command(
    TARGET StormySails POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
            "$<TARGET_FILE_DIR:StormySails>/shaders"
    COMMENT "copy shaders to StormySails build dir"
)

endif() # AMITY_BUILD_DEMOS


# Minecraft Voxel Game target (Minecraft)
add_executable(Minecraft
    src/games/Minecraft/main.cpp
    src/games/Minecraft/Minecraft.cpp
    src/games/Minecraft/Chunk.cpp
)
target_link_libraries(Minecraft PRIVATE AmityCore)
target_include_directories(Minecraft PRIVATE src/games/Minecraft)
target_include_directories(Minecraft PRIVATE src/third_party/stb)

# Post-Build Custom Command to copy shaders next to the Minecraft executable
add_custom_command(
    TARGET Minecraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
            "$<TARGET_FILE_DIR:Minecraft>/shaders"
    COMMENT "copy shaders to Minecraft build dir"
)


# build Private Games
if(AMITY_BUILD_PRIVATE_GAMES AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/games/PrivateGames/CMakeLists.txt")
    add_subdirectory(src/games/PrivateGames)
endif()

# Testing Suite Integration
if(AMITY_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
