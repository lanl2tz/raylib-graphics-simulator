# Collect source files
file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_subdirectory(grid)

# Include directories
target_include_directories(grid_lib PUBLIC ${PROJECT_SOURCE_DIR}/include/grid)