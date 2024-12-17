# Collect source files
file(GLOB_RECURSE SOURCE_FILES *.cpp)

# Create a library
add_library(grid ${SOURCE_FILES})

# Include directories
target_include_directories(grid PUBLIC ${PROJECT_SOURCE_DIR}/include)