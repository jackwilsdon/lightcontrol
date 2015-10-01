cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

project(lightcontrol)

add_subdirectory(deps)

set(lightcontrol_SOURCES
    src/serial_debug.c
    src/serial_linux.c
    src/serial_win.c
    src/main.c
)

set(lightcontrol_INCLUDES
    include
)

# Set include directory
include_directories(${lightcontrol_INCLUDES})

# Add source to executable
add_executable(lightcontrol ${lightcontrol_SOURCES})

# Add dependencies
target_link_libraries(lightcontrol packet)
