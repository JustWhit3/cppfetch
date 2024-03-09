# CMake project settings
cmake_minimum_required(VERSION 3.15)
project(cppfetch-examples
    VERSION 1.0
    DESCRIPTION "Build system for cppfetch examples."
    LANGUAGES CXX
)

# Directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Set compiler options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adding specific compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILE_FLAGS "/Wall /Yd /Oy /Gw")
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fno-omit-frame-pointer -fdata-sections -g")
    else()
        set(COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder -fdata-sections")
    endif()
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

# Create a function to launch executables
function(launch_exec)

    # Declare executables vars
    set(EXAMPLE_1 "cppfetch_example_1")

    # Create executables
    add_executable(${EXAMPLE_1} example_1.cpp)

    # Adding cppcheck properties
    find_program(CPPCHECK_FOUND cppcheck)
    if (CPPCHECK_FOUND AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(cppcheck_options "--enable=warning" "--inconclusive" "--force" "--inline-suppr")
        set_target_properties(${EXAMPLE_1} PROPERTIES CXX_CPPCHECK "${CPPCHECK_FOUND}")
    endif()

    # Link to OpenMP
    find_package(OpenMP REQUIRED)
    target_link_libraries(${EXAMPLE_1} PRIVATE OpenMP::OpenMP_CXX)

    # Link to cppfetch
    target_link_libraries(${EXAMPLE_1} PRIVATE cppfetch::cppfetch)
endfunction()

# Compile for every compiler except clang 14
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL "14.0.0")
    launch_exec()
endif()

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    launch_exec()
endif()