# License: MIT. See LICENSE in root directory.
# Date: 2020/06/29

cmake_minimum_required(VERSION 3.1.0)

project("ensemble-memory" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("${CMAKE_CURRENT_LIST_DIR}/inc")

set(ENSEMBLE_MEMORY_LIB "ensemble-memory-lib")
add_library(${ENSEMBLE_MEMORY_LIB} STATIC "")
target_sources(
    ${ENSEMBLE_MEMORY_LIB} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src/ensemble/memory.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/inc/ensemble/memory.hpp"
)

if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
    set(ENSEMBLE_MEMORY_EXE "ensemble-memory-exe")
    add_executable(
        ${ENSEMBLE_MEMORY_EXE}
        "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp"
    )
    target_link_libraries(
        ${ENSEMBLE_MEMORY_EXE}
        ${ENSEMBLE_MEMORY_LIB}
    )
endif ()
