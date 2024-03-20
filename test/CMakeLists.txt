# CMake project settings
cmake_minimum_required( VERSION 3.15 )

project( cppfetch-cpp-tests
    VERSION 1.0
    DESCRIPTION "Build system for cppfetch-cpp tests."
    LANGUAGES CXX
)

# Launch system and unit tests
add_subdirectory( unit_tests )