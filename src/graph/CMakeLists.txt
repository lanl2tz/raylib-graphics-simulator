# Collect source files
file(GLOB_RECURSE SOURCE_FILES *.cpp)

# Create a library
add_library(graph_lib ${SOURCE_FILES})

target_include_directories(graph_lib PUBLIC ${PROJECT_SOURCE_DIR}/include/graph)