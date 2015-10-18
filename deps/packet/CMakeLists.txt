cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

set(packet_SOURCES
    src/packet.c
)

set(packet_INCLUDES
    include
)

# Iterate each include file and add it to packet_INCLUDE_FILES
foreach(INCLUDE_PATH ${packet_INCLUDES})
    file(GLOB_RECURSE INCLUDE_FILES ${INCLUDE_PATH}/*)

    list(APPEND packet_INCLUDE_FILES ${INCLUDE_FILES})
endforeach(INCLUDE_PATH)

# Add source to library
add_library(packet STATIC ${packet_SOURCES} ${packet_INCLUDE_FILES})

# Add include directories to library
target_include_directories(packet PUBLIC ${packet_INCLUDES})
