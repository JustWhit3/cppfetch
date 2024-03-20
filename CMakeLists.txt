# Initial settings 
cmake_minimum_required(VERSION 3.15)
project(cppfetch-build
    VERSION 1.0
    DESCRIPTION "Build system for cppfetch."
    LANGUAGES CXX
)

# Build type settings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build type: DEBUG")
    add_compile_definitions(DEBUG_CPPFETCH)
else()
    message(STATUS "Build type: RELEASE")
endif()

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

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

# Creating the static library
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(cppfetch STATIC ${SRC_FILES})
add_library(cppfetch::cppfetch ALIAS cppfetch)

# Link to OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(cppfetch PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(cppfetch PRIVATE OpenMP::OpenMP_CXX)

# Adding cppcheck properties
find_program(CPPCHECK_FOUND cppcheck)
if (CPPCHECK_FOUND AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(cppcheck_options "--enable=warning" "--inconclusive" "--force" "--inline-suppr")
    set_target_properties(cppfetch PROPERTIES CXX_CPPCHECK "${CPPCHECK_FOUND}")
endif()

# Format the code
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    option(FORMAT "Format the code using clang-format" ON)
    if(FORMAT)
        find_program(CLANG_FORMAT_EXECUTABLE clang-format)
        if(CLANG_FORMAT_EXECUTABLE)
            message(STATUS "clang-format found: ${CLANG_FORMAT_EXECUTABLE}")
            file(GLOB_RECURSE SOURCE_FILES
                ${CMAKE_SOURCE_DIR}/src/*.cpp
                ${CMAKE_SOURCE_DIR}/include/cppfetch/*.hpp
                ${CMAKE_SOURCE_DIR}/examples/*.cpp
                ${CMAKE_SOURCE_DIR}/test/unit_tests/*.cpp
                ${CMAKE_SOURCE_DIR}/test/other_tests/*.cpp
            )
            add_custom_target(format
                COMMAND ${CLANG_FORMAT_EXECUTABLE}
                -i
                ${SOURCE_FILES}
            )
            add_dependencies(cppfetch format)
        else()
            message(STATUS "clang-format not found. Skipping code formatting.")
        endif()
    endif()
endif()

# Compiling examples
add_subdirectory(examples)

# Compile tests
option( CPPFETCH_TESTS "Enable / disable tests." ON )
if( CPPFETCH_TESTS )
    add_subdirectory( test )
else()
    message( STATUS "Skipping tests." )
endif()

# Setting installation paths
target_include_directories(cppfetch INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Installing headers
INSTALL(
    DIRECTORY include/cppfetch
    DESTINATION include
)

# Creating the package files
install(
    TARGETS cppfetch
    EXPORT cppfetchTargets
    DESTINATION lib
)

install(
    EXPORT cppfetchTargets
    FILE cppfetchTargets.cmake
    NAMESPACE cppfetch::
    DESTINATION lib/cmake/cppfetch
)

# Configure package files
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/cppfetchConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/cppfetch"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cppfetchConfigVersion.cmake"
  VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cppfetchConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cppfetchConfigVersion.cmake
    DESTINATION lib/cmake/cppfetch
)

export(EXPORT cppfetchTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cppfetchTargets.cmake"
)