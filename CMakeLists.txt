# CMakeList.txt : CMake project for Drawing a Triangle, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory")
endif()

project(VulkanTutorial
    VERSION 0.1
    DESCRIPTION "A simple Vulkan project, for practice"
    LANGUAGES CXX
    )

option(COMPILE_WITH_TESTS
    "Build the project using doctest"
    OFF)
if(COMPILE_WITH_TESTS)
  enable_testing()
else()
  add_definitions(-DDOCTEST_CONFIG_DISABLE)
endif()

# While I can't get library searching to work:
INCLUDE_DIRECTORIES (
    "$ENV{VK_SDK_PATH}/Include"
    C:/development_resources/glfw/glfw-3.3.bin.WIN64/include
    C:/development_resources/glm
    )
LINK_DIRECTORIES (
    "$ENV{VK_SDK_PATH}/Lib"
    C:/development_resources/glfw/glfw-3.3.bin.WIN64/lib-vc2019
    )

add_executable (vulkan_tutorial
    src/main.cpp
    src/HelloTriangleApplication.cpp src/HelloTriangleApplication.hpp
    src/VulkanHandler.cpp            src/VulkanHandler.hpp
    )
set_property(TARGET vulkan_tutorial PROPERTY CXX_STANDARD 17)
set_property(TARGET vulkan_tutorial PROPERTY CXX_STANDARD_REQUIRED ON)

TARGET_LINK_LIBRARIES (vulkan_tutorial
    vulkan-1
    glfw3
    )

# For certain editor plugins that need more information about compilation
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
add_custom_command(TARGET vulkan_tutorial
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    )

# TODO: Add tests and install targets if needed.

