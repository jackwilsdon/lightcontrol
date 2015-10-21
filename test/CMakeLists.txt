cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

project(control)

add_subdirectory(../deps ${CMAKE_BINARY_DIR}/deps)

set(test_SOURCES
    src/main.c
)

# Add source to executable
add_executable(run_tests ${test_SOURCES})

# Find CMocka
find_package(CMocka)

# Include CMocka
include_directories(${CMOCKA_INCLUDE_DIR})

# Add dependencies
target_link_libraries(run_tests packet cmocka)
