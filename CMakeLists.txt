cmake_minimum_required(VERSION 2.8.11)
project(z8e)

# look for CMakLists.txt in src directory too
subdirs(src)

# version info
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

# cmake info header file
configure_file (
    "${PROJECT_SOURCE_DIR}/src/cmake_config.h.in"
    "${PROJECT_BINARY_DIR}/cmake_config.h"
    )

# find includes in corresponding build dirs
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# place executable in binary dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
