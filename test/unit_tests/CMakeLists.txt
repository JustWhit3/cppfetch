# CMake project settings
cmake_minimum_required( VERSION 3.15 )

project( cppfetch-cpp-unit-tests
    VERSION 1.0
    DESCRIPTION "Build system for cppfetch-cpp unit tests."
    LANGUAGES CXX
)

# Set c++ standard options
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Other settings for paths
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../include )

# Create executables
set( UNIT "cppfetch_unit_tests" )
add_executable( ${UNIT} 
    tests_core.cpp 
)

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

# Linking to GTest
find_package(GTest REQUIRED)
target_link_libraries( ${UNIT} PRIVATE GTest::GTest GTest::Main )

# Link to OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(${UNIT} PRIVATE OpenMP::OpenMP_CXX)

# Link to cppfetch
target_link_libraries(${UNIT} PRIVATE cppfetch::cppfetch)

# Link to libcurl
find_package(CURL REQUIRED)
target_link_libraries(${UNIT} PRIVATE CURL::libcurl)