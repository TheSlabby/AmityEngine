cmake_minimum_required(VERSION 3.20)

# GoogleTest (from vcpkg "tests" feature)
find_package(GTest REQUIRED)

# Define the unit test executable
add_executable(AmityTests
    TestEntityComponent.cpp
    TestScene.cpp
    TestPanTilt.cpp
    TestUI.cpp
    TestUserInput.cpp
    TestPhysics.cpp
    TestEvent.cpp
    TestResourceManager.cpp
)

if(AMITY_ENABLE_LUA)
    target_sources(AmityTests PRIVATE TestScripting.cpp)
endif()

# Link tests to the Core engine and GoogleTest libraries
target_link_libraries(AmityTests PRIVATE
    AmityCore
    GTest::gtest
    GTest::gtest_main
)

# Register tests with CTest automatically
include(GoogleTest)
gtest_discover_tests(AmityTests)
