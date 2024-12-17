cmake_minimum_required(VERSION 3.10)
project(raylib-graphics-simulator LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Find the raylib package installed via Homebrew
find_package(raylib 5.5 REQUIRED) 
# Adjust the version number as needed based on the version installed.
# You can also omit the version, and just use: find_package(raylib REQUIRED)

# Add executable
add_executable(main src/main.cpp)

# Link raylib to your project
target_link_libraries(main PRIVATE raylib)

target_compile_features(main PRIVATE cxx_std_17)

target_include_directories(grid PUBLIC ${PROJECT_SOURCE_DIR}/include)
