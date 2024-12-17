# Collect source files
file(GLOB_RECURSE SOURCE_FILES *.cpp)

# Create a library
add_library(grid_lib ${SOURCE_FILES})

target_include_directories(grid_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)