# use all .c files in src directory
file(GLOB PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# look for generated include files
include_directories("${PROJECT_BINARY_DIR}")

# executable to build
add_executable(z8e ${PROJECT_SOURCES})
