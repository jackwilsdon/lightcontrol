cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

project(control)

add_subdirectory(../deps ${CMAKE_BINARY_DIR}/deps)

set(control_SOURCES
    src/serial_debug.c
    src/serial_linux.c
    src/serial_win.c
    src/main.c
)

set(control_INCLUDES
    include
)

# Set include directory
include_directories(${control_INCLUDES})

# Add source to executable
add_executable(control ${control_SOURCES})

# Add dependencies
target_link_libraries(control packet)
